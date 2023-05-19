#pragma once

#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(const std::string& path);
	~Model();

	void Render(ProgramObject* program, const glm::mat4& transform);
	void RenderInstanced(ProgramObject* program, const std::vector<glm::mat4>& transforms);

	std::vector<Mesh*> meshes;
private:
	std::string directory;

	void LoadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Tex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {};
};

