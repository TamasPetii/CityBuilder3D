#include "Model.h"

Model::Model(const std::string& path)
{
	LoadModel(path);
}

Model::~Model()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		if (meshes[i] != nullptr)
			delete meshes[i];
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Tex> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{

		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texture.x = mesh->mTextureCoords[0][i].x;
			vertex.texture.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texture.x = 0;
			vertex.texture.y = 0;
		}

		vertex.textureID = 0.f;

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		//Material Process
	}

	return new Mesh(vertices, indices, textures);
}



void Model::Render(ProgramObject* program, const glm::mat4& transform)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render(program, transform);
	}
}
void Model::RenderInstanced(ProgramObject* program, const std::vector<glm::mat4>& transforms)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->RenderInstanced(program, transforms);
	}
}