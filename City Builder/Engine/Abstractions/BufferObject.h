#pragma once

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

//Engine Headers
#include "Vertex.h"

//Standard Headers
#include <vector>

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

class VertexBufferObject : public BufferObject
{
public:
	VertexBufferObject() : BufferObject() {}

	void AttachStatic(const std::vector<Vertex>& vertices) const;
	void AttachDynamic(const std::vector<Vertex>& vertices) const;
};

class MatrixBufferObject : public BufferObject
{
public:
	MatrixBufferObject() : BufferObject() {}

	void AttachStatic(const std::vector<glm::mat4>& matrices) const;
	void AttachDynamic(const std::vector<glm::mat4>& matrices) const;
};

class IndexBufferObject : public BufferObject
{
public:
	IndexBufferObject() : BufferObject() {}

	void AttachStatic(const std::vector<GLuint>& indices);
	void AttachDynamic(const std::vector<GLuint>& indices);

	inline void Bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); };
	inline void UnBind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

	inline GLuint Get_IndexCount() const { return m_IndexCounter; }
private:
	GLuint m_IndexCounter = 0;
};

class VectorBufferObject : public BufferObject
{
public:
	VectorBufferObject() : BufferObject() {}

	void AttachStatic(const std::vector<glm::vec3>& vectors) const;
	void AttachDynamic(const std::vector<glm::vec3>& vectors) const;

	void AttachStatic(const std::vector<glm::vec2>& vectors) const;
	void AttachDynamic(const std::vector<glm::vec2>& vectors) const;
};