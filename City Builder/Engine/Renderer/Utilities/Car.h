#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <unordered_set>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

class RouteSection
{
public:
	RouteSection(glm::vec3 c1, glm::vec3 c2) {
		m_FirstPoint = c1; m_LastPoint = c2; m_MiddlePoint = glm::vec3(0); m_NumberOfCooordinates = 2; /*std::cout << c1.x << " " << c1.z << std::endl << c2.x << " " << c2.z << std::endl << std::endl*/;
	}
	RouteSection(glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) { m_FirstPoint = c1; m_MiddlePoint = c2; m_LastPoint = c3; m_NumberOfCooordinates = 3; }
	inline int Get_NumberOfCoordinates() { return m_NumberOfCooordinates; }

	glm::vec3 Get_FirstPoint() { return m_FirstPoint; }
	glm::vec3 Get_MiddlePoint() { return m_MiddlePoint; }
	glm::vec3 Get_LastPoint() { return m_LastPoint; }

private:
	glm::vec3 m_FirstPoint;
	glm::vec3 m_MiddlePoint;
	glm::vec3 m_LastPoint;

	int m_NumberOfCooordinates;
};

class Car
{
public:
	Car(std::vector<glm::vec3> coordinates);
	void Move(float t);
	glm::vec3 Get_CurrentPosition(float& rotation);
	glm::mat4 Get_Transform();

private:
	float m_Param = 0.0f;
	float m_Rotation = 0.0f;
	std::vector<RouteSection*> m_RouteSections;

};

class Cars
{
public:
	static std::vector<glm::mat4> Get_Transforms();
	static void Update();
private:
	static std::unordered_set<Car*> m_Cars;

	static float last_time;
	static float current_time;
	static float delta_time;
};