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
#include "Utilities/Camera.h"
#include "Utilities/Timer.h"
#include "Utilities/FrameCounter.h"
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
	void ConvertMouseInputTo3D(int xpos, int ypos, int width, int height);

	int DetermineRoadTextureID(int x, int y);
	void FireTruckSimulation();

private:
	GLFWwindow* m_Window = nullptr;
	Camera* m_Camera = nullptr;
	MyGui* m_MyGui = nullptr;
	City* m_City = nullptr;
	Timer* m_Timer = nullptr;
	FrameCounter* m_FrameCounter = nullptr;
private:
	glm::vec3 RayOrigin = glm::vec3(0);
	glm::vec3 RayEnd = glm::vec3(0);
	glm::vec3 RayDirection = glm::vec3(0);
	glm::vec3 RayHit = glm::vec3(0);

	bool changed = true;
	int m_WindowWidth = 0;
	int m_WindowHeight = 0;

	int HitX;
	int HitY;

	std::unordered_map<Car*, WaterGroup*> truck_map;
};

