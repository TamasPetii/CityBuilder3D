#include "BufferObject.h"

BufferObject::BufferObject()
{
	if (m_BufferID == 0) glGenBuffers(1, &m_BufferID);
}

BufferObject::~BufferObject()
{
	if (m_BufferID != 0) glDeleteBuffers(1, &m_BufferID);
}

//----------------|VertexBufferObject|----------------//

void VertexBufferObject::AttachStatic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void  VertexBufferObject::AttachDynamic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

//----------------|MatrixBufferObject|----------------//

void MatrixBufferObject::AttachStatic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_STATIC_DRAW);
}

void MatrixBufferObject::AttachDynamic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
}

//----------------|IndexBufferObject|----------------//

void IndexBufferObject::AttachStatic(const std::vector<GLuint>& indices) 
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void IndexBufferObject::AttachDynamic(const std::vector<GLuint>& indices)
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
}

//----------------|VectorBufferObject|----------------//

void VectorBufferObject::AttachStatic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_STATIC_DRAW);
}

void VectorBufferObject::AttachDynamic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_DYNAMIC_DRAW);
}

void VectorBufferObject::AttachStatic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_STATIC_DRAW);
}

void VectorBufferObject::AttachDynamic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_DYNAMIC_DRAW);
}