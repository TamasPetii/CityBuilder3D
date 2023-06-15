#include "BufferObject.h"

/**
 * Constructs a new BufferObject instance.
 *
 * @returns None
 */
BufferObject::BufferObject()
{
	if (m_BufferID == 0) glGenBuffers(1, &m_BufferID);
}

/**
 * Destructor for the BufferObject class.
 * Deletes the buffer object if it has been initialized.
 *
 * @returns None
 */
BufferObject::~BufferObject()
{
	if (m_BufferID != 0) glDeleteBuffers(1, &m_BufferID);
}

//----------------|VertexBufferObject|----------------//

/**
 * Attaches static vertex data to the vertex buffer object.
 *
 * @param vertices A vector of vertices to attach to the buffer.
 *
 * @returns None
 */
void VertexBufferObject::AttachDataStatic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic vertex data to the vertex buffer object.
 *
 * @param vertices A vector of vertices to be attached to the buffer.
 *
 * @returns None
 */
void  VertexBufferObject::AttachDataDynamic(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a subset of vertex data to the vertex buffer object.
 *
 * @param vertices A vector of vertices to be attached to the buffer.
 *
 * @returns None
 */
void VertexBufferObject::AttachSubData(const std::vector<Vertex>& vertices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
}

//----------------|TransformBufferObject|----------------//

/**
 * Attaches the given transforms to the buffer object and sets the buffer data usage to static.
 *
 * @param transforms The vector of transforms to attach to the buffer object.
 *
 * @returns None
 */
void TransformBufferObject::AttachDataStatic(const std::vector<Transform>& transforms) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(Transform), transforms.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic data to the buffer object.
 *
 * @param transforms A vector of Transform objects to be attached to the buffer object.
 *
 * @returns None
 */
void TransformBufferObject::AttachDataDynamic(const std::vector<Transform>& transforms) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(Transform), transforms.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a vector of transforms to the buffer object.
 *
 * @param transforms A vector of Transform objects to be attached to the buffer object.
 *
 * @returns None
 */
void TransformBufferObject::AttachSubData(const std::vector<Transform>& transforms) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, transforms.size() * sizeof(Transform), transforms.data());
}

//----------------|MatrixBufferObject|----------------//

/**
 * Attaches a vector of matrices to the buffer object.
 *
 * @param matrices A vector of matrices to be attached to the buffer object.
 *
 * @returns None
 */
void MatrixBufferObject::AttachDataStatic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic data to the buffer object.
 *
 * @param matrices A vector of matrices to be attached to the buffer object.
 *
 * @returns None
 */
void MatrixBufferObject::AttachDataDynamic(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a vector of matrices to the buffer object.
 *
 * @param matrices A vector of matrices to be attached to the buffer object.
 *
 * @returns None
 */
void MatrixBufferObject::AttachSubData(const std::vector<glm::mat4>& matrices) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
}

//----------------|IndexBufferObject|----------------//

/**
 * Attaches static index data to the IndexBufferObject.
 *
 * @param indices A vector of GLuint indices to be attached.
 *
 * @returns None
 */
void IndexBufferObject::AttachDataStatic(const std::vector<GLuint>& indices) 
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic data to the index buffer object.
 *
 * @param indices A vector of GLuint indices to be attached to the buffer.
 *
 * @returns None
 */
void IndexBufferObject::AttachDataDynamic(const std::vector<GLuint>& indices)
{
	m_IndexCounter = static_cast<GLuint>(indices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a subset of data to the index buffer object.
 *
 * @param indices A vector of GLuint indices to be attached.
 *
 * @returns None
 */
void IndexBufferObject::AttachSubData(const std::vector<GLuint>& indices) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
}

//----------------|VectorBufferObject|----------------//

/**
 * Attaches a static vector buffer object to the OpenGL context.
 *
 * @param vectors A vector of glm::vec3 objects to be attached to the buffer object.
 *
 * @returns None
 */
void VectorBufferObject::AttachDataStatic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic data to the buffer object.
 *
 * @param vectors A vector of glm::vec3 objects to be attached to the buffer object.
 *
 * @returns None
 */
void VectorBufferObject::AttachDataDynamic(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec3), vectors.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a sub-set of data to the buffer object.
 *
 * @param vectors A vector of glm::vec3 objects to be attached to the buffer object.
 *
 * @returns None
 */
void VectorBufferObject::AttachSubData(const std::vector<glm::vec3>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vectors.size() * sizeof(glm::vec3), vectors.data());
}

/**
 * Attaches a static vector buffer object to the GPU.
 *
 * @param vectors A vector of glm::vec2 objects to be attached to the buffer.
 *
 * @returns None
 */
void VectorBufferObject::AttachDataStatic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_STATIC_DRAW);
}

/**
 * Attaches a dynamic vector buffer object to the OpenGL context.
 *
 * @param vectors A vector of glm::vec2 objects to be attached to the buffer.
 *
 * @returns None
 */
void VectorBufferObject::AttachDataDynamic(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, vectors.size() * sizeof(glm::vec2), vectors.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a vector of glm::vec2 data to the buffer object.
 *
 * @param vectors The vector of glm::vec2 data to attach to the buffer object.
 *
 * @returns None
 */
void VectorBufferObject::AttachSubData(const std::vector<glm::vec2>& vectors) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vectors.size() * sizeof(glm::vec2), vectors.data());
}

//----------------|FloatBufferObject|----------------//

/**
 * Attaches the given data to the buffer object.
 *
 * @param numbers A vector of GLfloat values to be attached to the buffer object.
 *
 * @returns None
 */
void NumberBufferObject::AttachDataStatic(const std::vector<GLfloat>& numbers) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, numbers.size() * sizeof(GLfloat), numbers.data(), GL_STATIC_DRAW);
}

/**
 * Attaches dynamic data to the buffer object.
 *
 * @param numbers A vector of GLfloat values to be attached to the buffer object.
 *
 * @returns None
 */
void NumberBufferObject::AttachDataDynamic(const std::vector<GLfloat>& numbers) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, numbers.size() * sizeof(GLfloat), numbers.data(), GL_DYNAMIC_DRAW);
}

/**
 * Attaches a sub-set of data to the buffer object.
 *
 * @param numbers A vector of GLfloat values to be attached to the buffer object.
 *
 * @returns None
 */
void NumberBufferObject::AttachSubData(const std::vector<GLfloat>& numbers) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, numbers.size() * sizeof(GLfloat), numbers.data());
}
