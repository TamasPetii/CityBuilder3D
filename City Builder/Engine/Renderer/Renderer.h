#pragma once

//Abstractions
#include "../Abstractions/Model.h"
#include "../Abstractions/Camera.h"
#include "../Abstractions/FrameBuffer.h"
#include "../Abstractions/BufferObject.h"
#include "../Abstractions/VertexArrayObject.h"

//Shapes
#include "../Shapes/Basic Shapes/BasicShapes.h"
#include "../Shapes/Complex Shapes/ComplexShape.h"

class Renderer 
{
public:
	Renderer(Camera* camera);
	~Renderer();

	FrameBuffer* Get_FrameBuffer() { return m_FrameBuffer; }

	inline void Set_WindowSize(int w, int h) { m_Window_Width = w; m_Window_Height = h; }
	int m_Window_Width;
	int m_Window_Height;
	bool changed;
private: 

	void Init_Programs();
	void Delete_Programs();
	void Init_Textures();
	void Delete_Textures();

	Camera* m_Camera;
	ProgramObject* m_InstanceProgram = nullptr;
	ProgramObject* m_RayProgram = nullptr;
	ProgramObject* m_BaseProgram = nullptr;
	ProgramObject* m_SkyBoxProgram = nullptr;
	Texture2D* t_Texture = nullptr;
	FrameBuffer* m_FrameBuffer = nullptr;
	TextureMap* t_TextureSkybox = nullptr;
public:

	void Init_Models();
	void Init_BasicShapes();
	void Init_ComplexShapes();

	void Delete_Models();
	void Delete_BasicShapes();
	void Delete_ComplexShapes();

	void Render_Clear();
	void Render_PreRender(bool changed);
	void Render_PostRender();
	void Render_Axis();
	void Render_Ray(const glm::vec3& start, const glm::vec3& end);

	void RenderInstanced_Model(Model* model, const std::vector<glm::mat4>& transforms);
	void RenderInstanced_BasicShape(Shape* shape, const std::vector<glm::mat4>& transforms);
	void RenderInstanced_ComplexShape(Shape* shape, const std::vector<glm::mat4>& transforms);
	
	void RenderInstanced_Character(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Cube(const glm::mat4& transform, const glm::vec3& color);
	void RenderInstanced_Cone(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Sphere(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Pyramid(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Cylinder(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Residence1(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Residence2(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Residence3(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Industry1(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Industry2(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Industry3(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Service1(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Service2(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Service3(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_School1(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_School2(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_PowerStation(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_PowerWire(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_FireStation(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_PoliceStation(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Stadion(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Empty(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Road(const std::vector<glm::mat4>& transforms);
	void RenderInstanced_Forest(const std::vector<glm::mat4>& transforms);
private: 
	Model* m_Model = nullptr;
	Cube* r_Cube = nullptr;
	Cone* r_Cone = nullptr;
	Sphere* r_Sphere = nullptr;
	Pyramid* r_Pyramid = nullptr;
	Cylinder* r_Cylinder = nullptr;
	ResidenceBuilding1* r_Residence1 = nullptr;
	ResidenceBuilding2* r_Residence2 = nullptr;
	ResidenceBuilding3* r_Residence3 = nullptr;
	IndustryBuilding1* r_Industry1 = nullptr;
	IndustryBuilding2* r_Industry2 = nullptr;
	IndustryBuilding3* r_Industry3 = nullptr;
	ServiceBuilding1* r_Service1 = nullptr;
	ServiceBuilding2* r_Service2 = nullptr;
	ServiceBuilding3* r_Service3 = nullptr;
	SchoolBuilding1* r_School1 = nullptr;
	SchoolBuilding2* r_School2 = nullptr;
	PowerBuilding* r_PowerStation = nullptr;
	PowerWireBuilding* r_PowerWire = nullptr;
	PowerBuildingPlinth* r_PowerStationPlinth = nullptr;
	FireBuilding* r_FireStation = nullptr;
	PoliceBuilding* r_PoliceStation = nullptr;
	StadionBuilding* r_Stadion = nullptr;
	Ground* r_Ground = nullptr;
	Tree* r_Tree = nullptr;
};