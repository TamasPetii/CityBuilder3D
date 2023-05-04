#pragma once
#define _USE_MATH_DEFINES
#define WRITE(x) std::cout << x << std::endl;
#define WRITE_MAP(map) for(auto it = map.begin(); it != map.end(); it++) {std::cout << it->first << " " << it->second << std::endl;}


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
#include <fstream>
#include <utility>

class Application
{
public:
	Application(GLFWwindow* window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	~Application();

	void NewGame(int, int, int);
	void SaveGame();
	void LoadGame(bool b = false);
	std::vector<std::pair<FieldType, float*>> Get_TaxRates();
	void Update();
	void Render();
	void RenderUI();

	void Window_ResizedEvent(int width, int height);
	void FrameBuffer_ResizedEvent(int width, int height);
	void ConvertMouseInputTo3D(int xpos, int ypos, int width, int height);

	int DetermineRoadTextureID(int x, int y);
	void FireTruckSimulation();


	void SetUI_BuildCosts();

	void ViewPortEvent();
	void SaveGameEvent();
	void LoadGameEvent();
	void NewGameEvent();
	void TimeTickChangedEvent();
	void MeteorStartEvent();
	void TaxChangedEvent();
	void FpsChangedEvent();
	void CameraChangedEvent();
	void LightsChangedEvent();
	void LogChagendEvent();
	void DetailsCheckEvent();
	void MeteorHitEvent();
	void UpgradeEvent();

	void UpdateAnimationAndMembers();

	void BuildEvent();
	void BuildEvent_CheckField();
	void BuildEvent_Upgrade();
	void BuildEvent_SetFire();
	void BuildEvent_SendTruck();
	void BuildEvent_BuildField();

	void GameTickEvent();
	void GameTickEvent_SetGameUiMembers();
	void GameTickEvent_RandomMeteors();
	void GameTickEvent_RandomCars();
	void GameTickEvent_Fire();


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
	std::unordered_map<Car*, GameField*>  station_map;

	void CheckCarPos();

	bool InitLobby = true;
};

