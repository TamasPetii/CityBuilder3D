#pragma once
#define _USE_MATH_DEFINES

//OpenGL Headers
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

//Project Headers
#include "MyGui/MyGui.h"
#include "Abstractions/Camera.h"
#include "Renderer/Renderer.h"
#include "City.h"

//Std Headers
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Application
{
public:
	Application(GLFWwindow* window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	~Application();

	void Update();
	void Render();
	void RenderUI();

	void Window_ResizedEvent(int width, int height);
	void FrameBuffer_ResizedEvent(int width, int height);
	void Keyboard_ButtonEvent(int key, int scancode, int action, int mods);
	void Mouse_MoveEvent(double xpos, double ypos);
	void Mouse_ClickEvent(int button, int action, int mods);
	void Mouse_WeelEvent(double xoffset, double yoffset);

	void ConvertMouseInputTo3D(int xpos, int ypos, int width, int height);
private:
	GLFWwindow* m_Window = nullptr;
	Camera* m_Camera = nullptr;
	Renderer* m_Renderer = nullptr;
	MyGui* m_MyGui = nullptr;
	City* m_City = nullptr;
private:
	std::vector<glm::mat4> transforms_CUBE;
	std::vector<glm::mat4> transforms_CONE;
	std::vector<glm::mat4> transforms_CYLINDER;
	std::vector<glm::mat4> transforms_PYRAMID;
	std::vector<glm::mat4> transforms_SPHERE;
	std::vector<glm::mat4> transforms_RESIDENCE1;
	std::vector<glm::mat4> transforms_RESIDENCE2;
	std::vector<glm::mat4> transforms_RESIDENCE3;
	std::vector<glm::mat4> transforms_INDUSTRY1;
	std::vector<glm::mat4> transforms_INDUSTRY2;
	std::vector<glm::mat4> transforms_INDUSTRY3;
	std::vector<glm::mat4> transforms_SERVICE1;
	std::vector<glm::mat4> transforms_SERVICE2;
	std::vector<glm::mat4> transforms_SERVICE3;
	std::vector<glm::mat4> transforms_FIRESTATION;
	std::vector<glm::mat4> transforms_POLICESTATION;
	std::vector<glm::mat4> transforms_POWERSTATION;
	std::vector<glm::mat4> transforms_POWERWIRE;
	std::vector<glm::mat4> transforms_STADION;
	std::vector<glm::mat4> transforms_SCHOOL1;
	std::vector<glm::mat4> transforms_SCHOOL2;
	std::vector<glm::mat4> transforms_CHARACTER;
	std::vector<glm::mat4> transforms_FOREST;

	std::vector<glm::mat4> transforms_GROUND;
	std::vector<GLfloat> numbers_GROUND;

private:
	glm::vec3 RayOrigin = glm::vec3(0);
	glm::vec3 RayEnd = glm::vec3(0);
	glm::vec3 RayDirection = glm::vec3(0);
	glm::vec3 RayHit = glm::vec3(0);

	bool changed = true;
	int m_FrameCounter = 0;
	int m_WindowWidth = 0;
	int m_WindowHeight = 0;
};

