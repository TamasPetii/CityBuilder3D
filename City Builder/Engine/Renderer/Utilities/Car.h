#define _USE_MATH_DEFINES
#define VELOCITY 40

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

struct CarCoord
{
	glm::vec3 coord;
	bool isInterSection;
};

class RouteSection
{
public:
	RouteSection(CarCoord c1, CarCoord c2);
	RouteSection(CarCoord c1, CarCoord c2, CarCoord c3);

	inline void Increase_FirstX(float v) { m_FirstPoint.coord.x += v; }
	inline void Increase_FirstZ(float v) { m_FirstPoint.coord.z += v; }

	inline void Increase_MiddleX(float v) { m_MiddlePoint.coord.x += v; }
	inline void Increase_MiddleZ(float v) { m_MiddlePoint.coord.z += v; }

	inline void Increase_LastX(float v) { m_LastPoint.coord.x += v; }
	inline void Increase_LastZ(float v) { m_LastPoint.coord.z += v; }

	void CalculateSegmentLength();

	//Getters
	inline int Get_NumberOfCoordinates() { return m_NumberOfCooordinates; }
	inline glm::vec3 Get_FirstPoint() { return m_FirstPoint.coord; }
	inline glm::vec3 Get_MiddlePoint() { return m_MiddlePoint.coord; }
	inline glm::vec3 Get_LastPoint() { return m_LastPoint.coord; }
	inline float Get_Length() { return m_Length; }
	inline bool Get_IsInterSection() { return m_IsInterSection; }
	inline bool Get_IsInterSectionFirstCoord() { return m_FirstPoint.isInterSection; }
	inline bool Get_IsInterSectionMiddleCoord() { return m_MiddlePoint.isInterSection; }
	inline bool Get_IsInterSectionLastCoord() { return m_LastPoint.isInterSection; }

	//Setters
	inline void Set_FirstPoint(glm::vec3 point) { m_FirstPoint = { point }; }
	inline void Set_MiddlePoint(glm::vec3 point) { m_MiddlePoint = { point }; }
	inline void Set_LastPoint(glm::vec3 point) { m_LastPoint = { point }; }

private:
	CarCoord m_FirstPoint;
	CarCoord m_MiddlePoint;
	CarCoord m_LastPoint;

	int m_NumberOfCooordinates;
	float m_Length = 0;
	bool m_IsInterSection;
};

class Car
{
public:
	Car(std::vector<CarCoord> coordinates, bool isFireTruck);
	~Car();

	void Move(float t);
	bool ShouldBeDeleted() { return m_Param >= m_RouteSections.size(); }
	inline bool IsInIntersection() { return m_RouteSections[static_cast<int>(m_Param)]->Get_IsInterSection(); }

	//Getters
	glm::vec3 Get_CurrentPosition(float& rotation);
	glm::mat4 Get_Transform() { return glm::translate(Get_CurrentPosition(m_Rotation)) * glm::rotate(m_Rotation, glm::vec3(0, 1, 0)); }

	inline float Get_LocalParam() { return (m_Param - static_cast<int>(m_Param)); }
	inline float Get_Param() { return m_Param; }

	RouteSection* Get_CurrentRouteSection();
	RouteSection* Get_CurrentOriginalRouteSection();
	inline int Get_NumberOfRouteSections() { return static_cast<int>(m_RouteSections.size()); }
	inline RouteSection* Get_SpecificCurOrigRouteSection(int i) { return m_OriginalRouteSections[i]; }

	inline glm::mat4 Get_HitBoxTransform() { return glm::translate(Get_CurrentPosition(m_Rotation)); }
	HitBox Get_HitBox();

	inline float Get_LastMove() { return m_LastMove; }
	inline float Get_Rotation() { return m_Rotation; }
private:
	float m_Param = 0.0f;
	float m_Rotation = 0.0f;
	float m_LastMove = 0.0f;

	void AdjustCurveCoordinates(glm::vec3& coordinate1, glm::vec3& coordinate2, glm::vec3& coordinate3, float roadCompensation);
	void AdjustStraightCoordinates(glm::vec3& coordinate1, glm::vec3& coordinate2, float roadCompensation);

	void PrepareRoadSections(std::vector<CarCoord> coordinates, float roadCompensation);
	void CompensateCurves();
	void AdjustAdditionalSegments();

	void AddStraightSection(CarCoord coordinate1, CarCoord coordinate2, float roadCompensation);
	void AddCurveSection(CarCoord coord1, CarCoord coord2, CarCoord coord3, float roadCompensation);
	void AddSegmBetwIntersAndCurve(CarCoord coord1, CarCoord coord2, float roadCompensation);
	void AddSegmBetwCurveAndInters(CarCoord coord1, CarCoord coord2, CarCoord coord3, CarCoord coord4, CarCoord coord5, float roadCompensation);

	std::vector<RouteSection*> m_RouteSections;
	std::vector<RouteSection*> m_OriginalRouteSections;

	static HitBox m_HitBox;
};

class CarAndCoord
{
private:
	glm::vec3 m_Coord;
	Car* m_Car;
public:
	CarAndCoord(glm::vec3 coordinate, Car* car) { m_Coord = coordinate; m_Car = car; }

	//Getters
	inline glm::vec3 Get_Coord() const { return m_Coord; }
	inline Car* Get_Car() const { return m_Car; }
};

class CarGroup
{
public:
	static std::vector<glm::mat4> Get_Transforms();
	static std::vector<glm::mat4> Get_FireTruckTransforms();
	static void Update();
	static void ResetTimer();
	static void Add(std::vector<CarCoord>);
	static Car* AddFireTruck(std::vector<CarCoord> coords);
	static void Clear();
	static void ClearFireTrucks();
	static bool Intersect(Car* car1, Car* car2);

	//Setters
	static void Set_CarLimit(int limit) { car_limit = limit; }
	static std::unordered_set<Car*> m_FireTrucks;
	static std::unordered_set<Car*> m_Cars;
	static std::unordered_set<CarAndCoord*> m_InUseIntersections;
private:

	static float last_time;
	static float current_time;
	static float delta_time;
	static int car_limit;
};