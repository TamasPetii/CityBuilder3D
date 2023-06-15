#include "FrameBuffer.h"

/**
 * Constructs a new FrameBuffer object with default values.
 *
 * @param None
 *
 * @returns None
 */
FrameBuffer::FrameBuffer() :
	m_FrameBufferId(0),
	m_TextureId(0),
	m_DepthBufferId(0),
	m_Width(0),
	m_Height(0)
{

}

/**
 * Constructs a FrameBuffer object with the given width and height.
 *
 * @param width The width of the FrameBuffer.
 * @param height The height of the FrameBuffer.
 *
 * @returns None
 */
FrameBuffer::FrameBuffer(GLint width, GLint height)
{
	InitBuffers(width, height);
}

/**
 * Destructor for the FrameBuffer class.
 * Deletes all buffers associated with the FrameBuffer object.
 *
 * @returns None
 */
FrameBuffer::~FrameBuffer()
{
	DeleteBuffers();
}

/**
 * Initializes the frame buffer object with a texture and a depth buffer.
 *
 * @param width The width of the frame buffer.
 * @param height The height of the frame buffer.
 *
 * @returns None
 */
void FrameBuffer::InitBuffers(GLint width, GLint height)
{
	m_Width = width;
	m_Height = height;

	//Create FrameBuffer
	glGenFramebuffers(1, &m_FrameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);

	//Create and specify Texture
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Attach Texture to FrameBuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TextureId, 0);

	//Create and specify DepthBuffer
	glGenRenderbuffers(1, &m_DepthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferId);


	//Check Errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		exit(1);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * Deletes the frame buffer, depth buffer, and texture associated with the current FrameBuffer object.
 *
 * @returns None
 */
void FrameBuffer::DeleteBuffers()
{
	glDeleteFramebuffers(1, &m_FrameBufferId);
	glDeleteRenderbuffers(1, &m_DepthBufferId);
	glDeleteTextures(1, &m_TextureId);
}

/**
 * Resizes the frame buffer to the specified width and height.
 *
 * @param width The new width of the frame buffer.
 * @param height The new height of the frame buffer.
 *
 * @returns None
 */
void FrameBuffer::Resize(GLint width, GLint height)
{
	if (m_FrameBufferId == 0) return;
	if (width == m_Width && height == m_Height) return;

	DeleteBuffers();
	InitBuffers(width, height);
}

/**
 * Binds the framebuffer object and sets the viewport to the dimensions of the framebuffer.
 *
 * @param None
 *
 * @returns None
 */
void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);
	glViewport(0, 0, m_Width, m_Height);
}

/**
 * Unbinds the current framebuffer object and sets the default framebuffer as the active framebuffer.
 *
 * @returns None
 */
void FrameBuffer::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}