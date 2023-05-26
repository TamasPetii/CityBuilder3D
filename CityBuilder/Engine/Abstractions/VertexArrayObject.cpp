#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

void VertexArrayObject::LinkAttribute(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);

	buffer.UnBind();

}

void VertexArrayObject::LinkAttributeI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, type, stride, offset);

	buffer.UnBind();
}

void VertexArrayObject::LinkAttributeInstance(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glVertexAttribDivisor(layout, 1);

	buffer.UnBind();
}

void VertexArrayObject::LinkAttributeInstanceI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, type, stride, offset);
	glVertexAttribDivisor(layout, 1);

	buffer.UnBind();
}