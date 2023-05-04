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

#define MAX_SPEED 100

class Meteor
{
public:
	Meteor(float radius, float speed, glm::vec3 start, glm::vec3 end);
	bool Delete();
	void Update(float t);
	glm::mat4 Get_Transform();
	std::pair<int, int> Get_EndPos();
private:
	float t;
	float radius;
	float speed;
	glm::vec3 current_position;
	glm::vec3 start_position;
	glm::vec3 end_positon;
};

class MeteorGrp
{
public:
	static void Init();
	static void Clear();
	static void Update();
	static bool Effect();
	static void Delete();
	static void ResetTimer();
	static void Add(int x, int y);
	static std::vector<std::pair<int,int>> Change();
	static std::vector<glm::mat4> Get_Transforms();
private:
	static std::vector<Meteor*> m_ToDelete;
	static std::unordered_set<Meteor*> m_Meteors;

	static float last_time;
	static float current_time;
	static float delta_time;
};