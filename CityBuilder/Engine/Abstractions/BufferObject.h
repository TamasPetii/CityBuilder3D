#pragma once

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

//Engine Headers
#include "Vertex.h"
#include "Transform.h"

//Standard Headers
#include <vector>

/**
 * A BufferObject class that represents a buffer object in OpenGL.
 */
class BufferObject
{
public:
	BufferObject();
	virtual ~BufferObject();

	virtual inline void Bind()   const { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); };
	virtual inline void UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };

protected:
	GLuint m_BufferID = 0;
};

/**
 * A class representing a Vertex Buffer Object (VBO) that inherits from BufferObject.
 * A VBO is used to store vertex data such as position, color, and texture coordinates.
 */
class VertexBufferObject : public BufferObject
{
public:
	VertexBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<Vertex>& vertices) const;
	void AttachDataDynamic(const std::vector<Vertex>& vertices) const;
	void AttachSubData(const std::vector<Vertex>& vertices) const;
};

/**
 * A buffer object for storing transform data.
 */
class TransformBufferObject : public BufferObject
{
public:
	TransformBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<Transform>& transforms) const;
	void AttachDataDynamic(const std::vector<Transform>& transforms) const;
	void AttachSubData(const std::vector<Transform>& transforms) const;
};

/**
 * A buffer object for storing matrices.
 */
class MatrixBufferObject : public BufferObject
{
public:
	MatrixBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<glm::mat4>& matrices) const;
	void AttachDataDynamic(const std::vector<glm::mat4>& matrices) const;
	void AttachSubData(const std::vector<glm::mat4>& matrices) const;
};

/**
 * A class representing an Index Buffer Object in OpenGL.
 */
class IndexBufferObject : public BufferObject
{
public:
	IndexBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<GLuint>& indices);
	void AttachDataDynamic(const std::vector<GLuint>& indices);
	void AttachSubData(const std::vector<GLuint>& indices) const;

	inline void Bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); };
	inline void UnBind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

	inline GLuint Get_IndexCount() const { return m_IndexCounter; }
private:
	GLuint m_IndexCounter = 0;
};

/**
 * A class representing a buffer object for storing vectors.
 */
class VectorBufferObject : public BufferObject
{
public:
	VectorBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<glm::vec3>& vectors) const;
	void AttachDataDynamic(const std::vector<glm::vec3>& vectors) const;
	void AttachSubData(const std::vector<glm::vec3>& vectors) const;

	void AttachDataStatic(const std::vector<glm::vec2>& vectors) const;
	void AttachDataDynamic(const std::vector<glm::vec2>& vectors) const;
	void AttachSubData(const std::vector<glm::vec2>& vectors) const;
};

/**
 * A class representing a buffer object for storing numbers.
 */
class NumberBufferObject : public BufferObject
{
public:
	NumberBufferObject() : BufferObject() {}

	void AttachDataStatic(const std::vector<GLfloat>& numbers) const;
	void AttachDataDynamic(const std::vector<GLfloat>& numbers) const;
	void AttachSubData(const std::vector<GLfloat>& numbers) const;
};