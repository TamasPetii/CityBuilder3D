#include "Camera.h"

Camera::Camera(GLuint width, GLuint height)
{
	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);

	m_DirVec = glm::normalize(m_At - m_Eye);
	m_Yaw = glm::degrees(atan2f(m_DirVec.z, m_DirVec.x));
	m_Pitch = glm::degrees(asinf(m_DirVec.y));

	m_ViewMatrix = glm::lookAt(m_Eye, m_At, m_Up);
	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	GLfloat currentTime = static_cast<GLfloat>(glfwGetTime());
	m_DeltaTime = currentTime - m_LastTime;
	m_LastTime = currentTime;

	if (mode == THREE_DIMENSION)
	{
		m_Eye += m_Forward * m_DirVec * m_Speed * m_DeltaTime;
		m_Eye += m_Sideways * glm::normalize(glm::cross(m_DirVec, m_Up)) * m_Speed * m_DeltaTime;
	}
	else 
	{
		m_Eye += m_Sideways * glm::normalize(glm::cross(m_DirVec, m_Up)) * m_Speed * m_DeltaTime;
		m_Eye += m_Forward * glm::normalize(glm::cross(m_Up, glm::normalize(glm::cross(m_DirVec, m_Up)))) * m_Speed * m_DeltaTime;
		m_Eye += m_UpWays * m_Up * m_Speed * m_DeltaTime;
	}

	m_ViewMatrix = glm::lookAt(m_Eye, m_Eye + m_DirVec, m_Up);
}

//--------------|Keyboard Events|--------------//

void Camera::Keyboard_ButtonEvent(GLint key, GLint scancode, GLint action, GLint mods)
{
	if (action == GLFW_PRESS)
	{
		Keyboard_PressEvent(key);
	}
	else if (action == GLFW_RELEASE)
	{
		Keyboard_ReleaseEvent(key);
	}
}

void Camera::Keyboard_PressEvent(GLuint key)
{
	if (key == GLFW_KEY_W)
	{
		m_Forward = 1;
	}
	if (key == GLFW_KEY_S)
	{
		m_Forward = -1;
	}
	if (key == GLFW_KEY_A)
	{
		m_Sideways = -1;
	}
	if (key == GLFW_KEY_D)
	{
		m_Sideways = 1;
	}
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		m_UpWays = 1;
	}
	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		m_UpWays = -1;
	}
}

void Camera::Keyboard_ReleaseEvent(GLint key)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_S)
	{
		m_Forward = 0;
	}
	if (key == GLFW_KEY_A || key == GLFW_KEY_D)
	{
		m_Sideways = 0;
	}
	if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_LEFT_SHIFT)
	{
		m_UpWays = 0;
	}
}

//--------------|Mouse Events|--------------//

void Camera::Mouse_ClickEvent(GLint button, GLint action, GLint mods)
{
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_IsMovable = true;
	}
	else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_IsMovable = false;
		m_InitCursorPos = true;
	}
}

void Camera::Mouse_MoveEvent(GLfloat xpos, GLfloat ypos)
{
	if (!m_IsMovable) return;

	if (m_InitCursorPos)
	{
		m_CursorStartX = xpos;
		m_CursorStartY = ypos;
		m_InitCursorPos = false;
	}

	GLfloat offsetX = xpos - m_CursorStartX;
	GLfloat offsetY = m_CursorStartY - ypos;

	m_CursorStartX = xpos;
	m_CursorStartY = ypos;

	float sensitivity = 0.2f * (m_Fov / 60.f);
	offsetX *= sensitivity;
	offsetY *= sensitivity;


	m_Yaw += offsetX;
	m_Pitch += offsetY;
	m_Pitch = glm::clamp(m_Pitch, -89.f, 89.f);

	glm::vec3 direction(
		cosf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch)),
		sinf(glm::radians(m_Pitch)),
		sinf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch))
	);

	m_At = m_Eye + direction;

	m_DirVec = glm::normalize(m_At - m_Eye);
}

void Camera::Mouse_WheelEvent(GLfloat xoffset, GLfloat yoffset)
{
	m_Fov -= yoffset;
	m_Fov = glm::clamp(m_Fov, 1.f, 60.f);

	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

//--------------|Setter|--------------//

void Camera::Set_ProjMatrix(GLuint width, GLuint height)
{
	if (height == 0) return;

	glViewport(0, 0, width, height);

	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);

	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

void Camera::Set_ProjMatrix(GLfloat fov, GLuint width, GLuint height)
{
	glViewport(0, 0, width, height);

	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);
	m_Fov = fov;
	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

void Camera::Set_ProjMatrix(GLfloat fov, GLuint width, GLuint height, GLfloat near, GLfloat far)
{
	glViewport(0, 0, width, height);

	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);
	m_Fov = fov;
	m_Near = near;
	m_Far = far;
	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

void Camera::Set_Eye(const glm::vec3& eye)
{
	m_Eye = eye;

	m_ViewMatrix = glm::lookAt(m_Eye, m_At, m_Up);
	m_DirVec = glm::normalize(m_At - m_Eye);
	m_Yaw = glm::degrees(atan2f(m_DirVec.z, m_DirVec.x));
	m_Pitch = glm::degrees(asinf(m_DirVec.y));
}

void Camera::Set_At(const glm::vec3& at)
{
	m_At = at;

	m_ViewMatrix = glm::lookAt(m_Eye, m_At, m_Up);
	m_DirVec = glm::normalize(m_At - m_Eye);
	m_Yaw = glm::degrees(atan2f(m_DirVec.z, m_DirVec.x));
	m_Pitch = glm::degrees(asinf(m_DirVec.y));
}

void Camera::Set_Mode(int mode, int x, int y)
{
	m_IsMovable = true;

	if (mode == TWO_DIMENSION)
	{
		m_Yaw = -90.f;
		m_Pitch = -89.f;
		Mouse_MoveEvent((GLfloat)x, (GLfloat)y);
		this->mode = (Mode)mode;
	}
	else if (mode == TWO_HALF_DIMENSION)
	{
		m_Yaw = -90.f;
		m_Pitch = -26.565f;
		Mouse_MoveEvent((GLfloat)x, (GLfloat)y);
		this->mode = (Mode)mode;
	}
	else if(mode == THREE_DIMENSION)
	{
		this->mode = (Mode)mode;
	}

	m_IsMovable = false;
}