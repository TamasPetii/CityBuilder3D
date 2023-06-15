#pragma once

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

//Engine Headers
#include "Vertex.h"
#include "BufferObject.h"

//Standard Headers
#include <vector>

/**
 * A class representing a Vertex Array Object (VAO) in OpenGL.
 */
class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	inline void Bind() const   { glBindVertexArray(m_VertexArrayID); }
	inline void UnBind() const { glBindVertexArray(0); }

	void LinkAttribute(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const;
	void LinkAttributeI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const;

	void LinkAttributeInstance(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const;
	void LinkAttributeInstanceI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const;

private:
	GLuint m_VertexArrayID;
};

