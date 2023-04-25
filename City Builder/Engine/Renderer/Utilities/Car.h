#define _USE_MATH_DEFINES
#define VELOCITY 20

#include <vector>
#include <iostream>
#include <unordered_set>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/transform2.hpp>

struct HitBox
{
	glm::vec3 min;
	glm::vec3 max;
};

class RouteSection
{
public:
	RouteSection(glm::vec3 c1, glm::vec3 c2) { m_FirstPoint = c1; m_LastPoint = c2; m_MiddlePoint = glm::vec3(0); m_NumberOfCooordinates = 2; }
	RouteSection(glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) { m_FirstPoint = c1; m_MiddlePoint = c2; m_LastPoint = c3; m_NumberOfCooordinates = 3; }
	inline int Get_NumberOfCoordinates() { return m_NumberOfCooordinates; }

	inline glm::vec3 Get_FirstPoint() { return m_FirstPoint; }
	inline glm::vec3 Get_MiddlePoint() { return m_MiddlePoint; }
	inline glm::vec3 Get_LastPoint() { return m_LastPoint; }
	inline float Get_Length() { return m_Length; }
	

	inline void Increase_FirstX(float v) { m_FirstPoint.x += v; }
	inline void Increase_FirstZ(float v) { m_FirstPoint.z += v; }

	inline void Increase_MiddleX(float v) { m_MiddlePoint.x += v; }
	inline void Increase_MiddleZ(float v) { m_MiddlePoint.z += v; }

	inline void Increase_LastX(float v) { m_LastPoint.x += v; }
	inline void Increase_LastZ(float v) { m_LastPoint.z += v; }

	void CalculateSegmentLength();

private:
	glm::vec3 m_FirstPoint;
	glm::vec3 m_MiddlePoint;
	glm::vec3 m_LastPoint;

	int m_NumberOfCooordinates;
	float m_Length = 0;
};

class Car
{
public:
	Car(std::vector<glm::vec3> coordinates);
	~Car();
	void Move(float t);
	glm::vec3 Get_CurrentPosition(float& rotation);
	glm::mat4 Get_Transform();
	glm::mat4 Get_HitBoxTransform();
	bool ShouldBeDeleted() { return m_Param >= m_RouteSections.size(); }
	inline float Get_LastMove() { return m_LastMove; }
	inline float Get_LocalParam() { return (m_Param - static_cast<int>(m_Param)); }
	RouteSection* Get_CurrentRouteSection();
	HitBox Get_HitBox();

private:
	float m_LastMove = 0.0f;
	float m_Param = 0.0f;
	float m_Rotation = 0.0f;
	std::vector<RouteSection*> m_RouteSections;

	static HitBox m_HitBox;

};

class Cars
{
public:
	static std::vector<glm::mat4> Get_Transforms();
	static void Update();
	static void Add(std::vector<glm::vec3>);
	static void Clear();
	static bool Intersect(Car* car1, Car* car2);
private:
	static std::unordered_set<Car*> m_Cars;

	static float last_time;
	static float current_time;
	static float delta_time;
};