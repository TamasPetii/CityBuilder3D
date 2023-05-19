#pragma once

//OpenGL Header Files
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

#include <iostream>

enum Mode {TWO_DIMENSION, TWO_HALF_DIMENSION, THREE_DIMENSION };

class Camera
{
public:

	Camera(GLuint width, GLuint height);
	~Camera();

	void Update();

	void Keyboard_ButtonEvent(GLint key, GLint scancode, GLint action, GLint mods);
	void Mouse_WheelEvent(GLfloat xoffset, GLfloat yoffset);
	void Mouse_ClickEvent(GLint button, GLint action, GLint mods);
	void Mouse_MoveEvent(GLfloat xpos, GLfloat ypos);

	//Setter
	void Set_Eye(const glm::vec3& eye);
	void Set_At(const glm::vec3& at);
	void Set_ProjMatrix(GLuint width, GLuint height);
	void Set_ProjMatrix(GLfloat fov, GLuint width, GLuint height);
	void Set_ProjMatrix(GLfloat fov, GLuint width, GLuint height, GLfloat near, GLfloat far);
	void Set_Mode(int mode, int x, int y);
	//Getter
	inline GLfloat Get_Width() const { return m_Width; }
	inline GLfloat Get_Height() const { return m_Heigth; }

	inline glm::mat4 Get_ProjMatrix() const { return m_ProjMatrix; }
	inline glm::mat4 Get_ViewMatrix() const { return m_ViewMatrix; }
	inline glm::mat4 Get_ViewProjMatrix() const { return m_ProjMatrix * m_ViewMatrix; }

	inline glm::vec3 Get_CameraEye() const { return m_Eye; }
	inline glm::vec3 Get_CameraAt() const { return m_At; }
	inline glm::vec3 Get_CameraUp() const { return m_Up; }

	inline GLfloat& Get_Speed() { return m_Speed; }
	inline int& Get_Mode() { return mode; }

	void ResetTimer() { m_LastTime = glfwGetTime(); }

protected:
	void Keyboard_PressEvent(GLuint key);
	void Keyboard_ReleaseEvent(GLint key);
private:
	GLfloat m_DeltaTime = 0.f;
	GLfloat m_LastTime = 0.f;

	GLfloat m_Speed = 5.f;
	GLfloat m_Forward = 0.f;
	GLfloat m_Sideways = 0.f;
	GLfloat m_UpWays = 0.f;

	glm::vec3 m_Eye = glm::vec3(0.f, 1.f, 2.5f);
	glm::vec3 m_At  = glm::vec3(0.f, 0.f, 0.f );
	glm::vec3 m_Up  = glm::vec3(0.f, 1.f, 0.f );

	GLfloat m_Fov = 60.f;
	GLfloat m_Width = 0.f;
	GLfloat m_Heigth = 0.f;
	GLfloat m_Near = 0.1f;
	GLfloat m_Far = 1000.f;

	glm::vec3 m_DirVec = glm::vec3(0.f);
	GLfloat m_Yaw = 0.f;
	GLfloat m_Pitch = 0.f;

	GLfloat m_CursorStartX = 0.f;
	GLfloat m_CursorStartY = 0.f;
	GLboolean m_InitCursorPos = true;
	GLboolean m_IsMovable = false;

	glm::mat4 m_ProjMatrix = glm::mat4(1);
	glm::mat4 m_ViewMatrix = glm::mat4(1);

	int mode = THREE_DIMENSION;
};