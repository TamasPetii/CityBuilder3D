#include "Shape.h"

void Shape::ConcatenateVertices(std::vector<Vertex>& vertices0, std::vector<Vertex> vertices1)
{
	vertices0.insert(vertices0.end(), vertices1.begin(), vertices1.end());
}

void Shape::ConcatenateIndices(std::vector<GLuint>& indices0, std::vector<GLuint> indices1)
{
	indices0.insert(indices0.end(), indices1.begin(), indices1.end());
}

//-----------------------------------------------------------NON-STATIC-----------------------------------------------------------//

void Shape::Bind() const
{
	m_VAO.Bind();
}
void Shape::UnBind() const
{
	m_VAO.UnBind();
}

void Shape::Render() const
{
	glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr);
}

void Shape::RenderInstanced() const
{
	glDrawElementsInstanced(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, nullptr, m_InstanceCount);
}

void Shape::AttachMatrices(const std::vector<glm::mat4>& transforms)
{
	m_MAT.AttachDynamic(transforms);
	m_InstanceCount = static_cast<GLuint>(transforms.size());
}

void Shape::AttachToGPU(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	m_IndicesCount = static_cast<GLuint>(indices.size());

	m_VAO.Bind();

	m_VBO.AttachStatic(vertices);
	m_IBO.AttachStatic(indices);
	m_MAT.AttachDynamic({});

	m_VAO.LinkAttribute(m_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
	m_VAO.LinkAttribute(m_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (const void*)(1 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3)));
	m_VAO.LinkAttribute(m_VBO, 3, 1, GL_FLOAT, sizeof(Vertex), (const void*)(2 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2)));

	m_VAO.LinkAttributeInstance(m_MAT, 4, 4, GL_FLOAT, sizeof(glm::mat4), nullptr);
	m_VAO.LinkAttributeInstance(m_MAT, 5, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(1 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MAT, 6, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(2 * sizeof(glm::vec4)));
	m_VAO.LinkAttributeInstance(m_MAT, 7, 4, GL_FLOAT, sizeof(glm::mat4), (const void*)(3 * sizeof(glm::vec4)));

	m_VAO.UnBind();
	m_VBO.UnBind();
	m_IBO.UnBind();
	m_MAT.UnBind();
}