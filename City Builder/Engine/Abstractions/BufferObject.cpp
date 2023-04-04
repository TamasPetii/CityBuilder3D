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

void VertexBufferObject::AttachDataStatic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void  VertexBufferObject::AttachDataDynamic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

void VertexBufferObject::AttachSubData(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
}

//----------------|MatrixBufferObject|----------------//

void MatrixBufferObject::AttachDataStatic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_STATIC_DRAW);
}

void MatrixBufferObject::AttachDataDynamic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
}

void MatrixBufferObject::AttachSubData(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
}

//----------------|IndexBufferObject|----------------//

void IndexBufferObject::AttachDataStatic(const std::vector<GLuint>& indices) 
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void IndexBufferObject::AttachDataDynamic(const std::vector<GLuint>& indices)
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
}

void IndexBufferObject::AttachSubData(const std::vector<GLuint>& indices) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
}

//----------------|VectorBufferObject|----------------//

void VectorBufferObject::AttachDataStatic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_STATIC_DRAW);
}

void VectorBufferObject::AttachDataDynamic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_DYNAMIC_DRAW);
}

void VectorBufferObject::AttachSubData(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, vectors.size() * sizeof(glm::vec3), vectors.data());
}

void VectorBufferObject::AttachDataStatic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_STATIC_DRAW);
}

void VectorBufferObject::AttachDataDynamic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_DYNAMIC_DRAW);
}

void VectorBufferObject::AttachSubData(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, vectors.size() * sizeof(glm::vec2), vectors.data());
}