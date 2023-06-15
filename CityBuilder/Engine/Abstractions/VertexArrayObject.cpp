#include "VertexArrayObject.h"

/**
 * Constructs a new VertexArrayObject by generating a unique ID for the vertex array.
 *
 * @returns None
 */
VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

/**
 * Destructor for the VertexArrayObject class.
 * Deletes the vertex array object.
 *
 * @returns None
 */
VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

/**
 * Links a buffer object to a vertex attribute in the vertex array object.
 *
 * @param buffer The buffer object to link.
 * @param layout The layout of the vertex attribute.
 * @param size The number of components per vertex attribute.
 * @param type The data type of each component in the vertex attribute.
 * @param stride The byte offset between consecutive generic vertex attributes.
 * @param offset The offset of the first component of the first vertex attribute in the buffer.
 *
 * @returns None
 */
void VertexArrayObject::LinkAttribute(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);

	buffer.UnBind();

}

/**
 * Links an integer attribute to a vertex buffer object.
 *
 * @param buffer The buffer object to link the attribute to.
 * @param layout The layout of the attribute.
 * @param size The number of components per vertex attribute.
 * @param type The data type of each component in the attribute.
 * @param stride The byte offset between consecutive generic vertex attributes.
 * @param offset The offset of the first component of the first generic vertex attribute in the array.
 *
 * @returns None
 */
void VertexArrayObject::LinkAttributeI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, type, stride, offset);

	buffer.UnBind();
}

/**
 * Links an attribute instance to a buffer object and sets up the vertex attribute pointer.
 *
 * @param buffer The buffer object to link the attribute instance to.
 * @param layout The layout of the attribute instance.
 * @param size The size of the attribute instance.
 * @param type The data type of the attribute instance.
 * @param stride The stride of the attribute instance.
 * @param offset The offset of the attribute instance.
 *
 * @returns None
 */
void VertexArrayObject::LinkAttributeInstance(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glVertexAttribDivisor(layout, 1);

	buffer.UnBind();
}

/**
 * Links an integer attribute to a vertex buffer object and sets the divisor to 1.
 *
 * @param buffer The buffer object to link the attribute to.
 * @param layout The layout of the attribute.
 * @param size The size of the attribute.
 * @param type The data type of the attribute.
 * @param stride The stride of the attribute.
 * @param offset The offset of the attribute.
 *
 * @returns None
 */
void VertexArrayObject::LinkAttributeInstanceI(const BufferObject& buffer, GLuint layout, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) const
{
	buffer.Bind();

	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, type, stride, offset);
	glVertexAttribDivisor(layout, 1);

	buffer.UnBind();
}