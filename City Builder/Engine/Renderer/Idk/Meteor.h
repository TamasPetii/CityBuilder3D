#pragma once

#define _USE_MATH_DEFINES

#include <unordered_set>
#include <vector>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <random>

struct MeteorLayout
{
	float speed;
	float radius;
	glm::vec3 start_position;
	glm::vec3 end_positon;
	glm::vec3 current_position;
};

class Meteor
{
public:
	static bool Init;

	static void AdjustTime();


	static void FullClear();
	static void Clear();
	static void Update();
	static void Add(int x, int y);

	static bool IsActive();

	static std::vector<glm::mat4> Get_Transforms();
	static std::vector<std::pair<int, int>> Get_Fields();
private:
	static std::vector<MeteorLayout*> to_delete;
	static std::vector<std::pair<int, int>> fields;
	static std::unordered_set<MeteorLayout*> meteors;

	static float last_time;
	static float current_time;
};

