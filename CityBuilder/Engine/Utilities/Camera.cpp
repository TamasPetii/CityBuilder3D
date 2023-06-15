#include "Camera.h"

/**
 * Constructs a Camera object with the given width and height.
 *
 * @param width The width of the camera viewport.
 * @param height The height of the camera viewport.
 *
 * @returns None
 */
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

/**
 * Destructor for the Camera class.
 *
 * @param None
 *
 * @returns None
 */
Camera::~Camera()
{
}

/**
 * Updates the camera position and view matrix based on the current mode and input.
 *
 * @returns None
 */
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

/**
 * Handles keyboard button events for the camera.
 *
 * @param key The keyboard key that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action The action that was taken on the key (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
 * @param mods Bit field describing which modifier keys were held down.
 *
 * @returns None
 */
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

/**
 * Handles keyboard press events for the camera.
 *
 * @param key The key that was pressed.
 *
 * @returns None
 */
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

/**
 * Handles the release of a keyboard key event for the camera.
 *
 * @param key The key that was released.
 *
 * @returns None
 */
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

/**
 * Handles mouse click events for the camera.
 *
 * @param button The button that was clicked.
 * @param action The action that was performed (e.g. press, release).
 * @param mods Any modifier keys that were pressed (e.g. shift, alt).
 *
 * @returns None
 */
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

/**
 * Handles mouse movement events for the camera.
 *
 * @param xpos The x-coordinate of the mouse cursor.
 * @param ypos The y-coordinate of the mouse cursor.
 *
 * @returns None
 */
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

/**
 * Handles mouse wheel events to zoom in or out of the camera view.
 *
 * @param xoffset The horizontal offset of the mouse wheel.
 * @param yoffset The vertical offset of the mouse wheel.
 *
 * @returns None
 */
void Camera::Mouse_WheelEvent(GLfloat xoffset, GLfloat yoffset)
{
	m_Fov -= yoffset;
	m_Fov = glm::clamp(m_Fov, 1.f, 60.f);

	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

//--------------|Setter|--------------//

/**
 * Sets the projection matrix of the camera.
 *
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 *
 * @returns None
 */
void Camera::Set_ProjMatrix(GLuint width, GLuint height)
{
	if (height == 0) return;

	glViewport(0, 0, width, height);

	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);

	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

/**
 * Sets the projection matrix of the camera.
 *
 * @param fov The field of view of the camera.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 *
 * @returns None
 */
void Camera::Set_ProjMatrix(GLfloat fov, GLuint width, GLuint height)
{
	glViewport(0, 0, width, height);

	m_Width = static_cast<GLfloat>(width);
	m_Heigth = static_cast<GLfloat>(height);
	m_Fov = fov;
	m_ProjMatrix = glm::perspective(glm::radians(m_Fov), m_Width / m_Heigth, m_Near, m_Far);
}

/**
 * Sets the projection matrix of the camera.
 *
 * @param fov The field of view of the camera.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 * @param near The distance to the near clipping plane.
 * @param far The distance to the far clipping plane.
 *
 * @returns None
 */
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

/**
 * Sets the position of the camera's eye and updates the view matrix, direction vector, yaw, and pitch.
 *
 * @param eye The new position of the camera's eye.
 *
 * @returns None
 */
void Camera::Set_Eye(const glm::vec3& eye)
{
	m_Eye = eye;

	m_ViewMatrix = glm::lookAt(m_Eye, m_At, m_Up);
	m_DirVec = glm::normalize(m_At - m_Eye);
	m_Yaw = glm::degrees(atan2f(m_DirVec.z, m_DirVec.x));
	m_Pitch = glm::degrees(asinf(m_DirVec.y));
}

/**
 * Sets the "at" position of the camera and updates the view matrix, direction vector, yaw, and pitch.
 *
 * @param at The new "at" position of the camera.
 *
 * @returns None
 */
void Camera::Set_At(const glm::vec3& at)
{
	m_At = at;

	m_ViewMatrix = glm::lookAt(m_Eye, m_At, m_Up);
	m_DirVec = glm::normalize(m_At - m_Eye);
	m_Yaw = glm::degrees(atan2f(m_DirVec.z, m_DirVec.x));
	m_Pitch = glm::degrees(asinf(m_DirVec.y));
}

/**
 * Sets the camera mode and orientation based on the input mode and position.
 *
 * @param mode The camera mode to set.
 * @param x The x-coordinate of the camera position.
 * @param y The y-coordinate of the camera position.
 *
 * @returns None
 */
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