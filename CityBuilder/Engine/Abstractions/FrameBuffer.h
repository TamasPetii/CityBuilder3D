#pragma once

//OpenGL Header Files
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(GLint width, GLint height);
	~FrameBuffer();

	void InitBuffers(GLint width, GLint height);
	void DeleteBuffers();

	void Resize(GLint width, GLint height);

	void Bind() const;
	void UnBind() const;

	inline GLuint Get_FrameBufferId() const { return m_FrameBufferId; }
	inline GLuint Get_TextureId() const { return m_TextureId; }
	inline GLint Get_FrameWidth() const { return m_Width; }
	inline GLint Get_FrameHeight() const { return m_Height; }
private:
	GLuint m_FrameBufferId;
	GLuint m_TextureId;
	GLuint m_DepthBufferId;

	GLint m_Width;
	GLint m_Height;
};