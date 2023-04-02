#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Tex>& textures) :
	textures(textures)
{
	std::cout << "MESH: " << vertices.size() << " " << indices.size() << std::endl;
	AttachToGPU(vertices, indices);
}

void Mesh::AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	m_IndicesCount = (GLuint)indices.size();

	m_VAO.Bind();

	m_VBO.AttachStatic(vertices);
	m_IBO.AttachStatic(indices);
	m_MBO.AttachDynamic({});

	m_VAO.LinkAttribute(m_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
	m_VAO.LinkAttribute(m_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (const void*)(1 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 3, 1, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2)));

	m_VAO.LinkAttributeInstance(m_MBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), nullptr);
	m_VAO.LinkAttributeInstance(m_MBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(1 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(2 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MBO, 7, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(3 * sizeof(glm::vec4)));

	m_VAO.UnBind();
	m_VBO.UnBind();
	m_IBO.UnBind();
	m_MBO.UnBind();
}

void Mesh::Render(ProgramObject* program, const glm::mat4& transform)
{
	program->Bind();
	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr);
	m_VAO.UnBind();
	program->UnBind();
}
void Mesh::RenderInstanced(ProgramObject* program, const std::vector<glm::mat4>& transforms)
{
	m_InstanceCount = (GLuint)transforms.size();

	program->Bind();
	m_VAO.Bind();
	m_MBO.AttachDynamic(transforms);
	glDrawElementsInstanced(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr, m_InstanceCount);
	m_MBO.AttachDynamic({});
	m_VAO.UnBind();
	program->UnBind();
}
