#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <cmath>
#include <random>
#include <unordered_set>
#include <vector>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

class ProjectileMotion;
class Water;

class WaterGroup
{
public:
	WaterGroup(float startX, float startY, float endX, float endY);
	void Init();
	void Clear();
	void Update();
	void Recalculate(int endX, int endY);
	void Delete();
	void Add();
	void ResetTimer();
	std::vector<glm::mat4> Get_Transforms();

	float startX;
	float startY;
	float endX;
	float endY;
private:

	std::vector<Water*> m_ToDelete;
	std::unordered_set<Water*> m_Waters;
	ProjectileMotion* curve;

	float time = 0;
	float last_time;
	float current_time;
	float delta_time;
};

class Water
{
public:
	Water();
	void Update(float t, ProjectileMotion* curve);
	bool Delete();
	inline glm::mat4 Get_Transform() { return glm::translate(position); }
private:
	float t = 0;
	glm::vec3 position;
};

class ProjectileMotion
{
public:
	ProjectileMotion(glm::vec3 start, glm::vec3 end);
	glm::vec3 Get_PositionOnCurve(float t);
private:
	glm::vec3 m_MotionStartPosition;
	glm::vec3 m_MotionEndPosition;
	float m_Gravity = 9.81f;

	float distanceX;
	float distanceZ;
	float distanceY;
	float distance;
	float angle;
	float speed;
};

