#pragma once

#define _USE_MATH_DEFINES

//Abstractions
#include "../Abstractions/Model.h"
#include "../Abstractions/Camera.h"
#include "../Abstractions/FrameBuffer.h"
#include "../Abstractions/BufferObject.h"
#include "../Abstractions/VertexArrayObject.h"

//Shapes
#include "../Shapes/Basic Shapes/BasicShapes.h"
#include "../Shapes/Complex Shapes/ComplexShape.h"
#include "SkyBox/Skybox.h"
#include "RendererLayout.h"

#include <cmath>

class Renderer 
{
public:
	Renderer(Camera* camera);
	~Renderer();
public:

	FrameBuffer* Get_FrameBuffer() { return m_FrameBuffer; }

	inline void Set_WindowSize(int w, int h) { m_Window_Width = w; m_Window_Height = h; }
	int m_Window_Width;
	int m_Window_Height;
	bool changed;
	bool buildable;

	void Render_Clear();
	void Render_Axis();
	void Render_Ray(const glm::vec3& start, const glm::vec3& end);

	void Render_PreRender(bool changed);
	void Render_PostRender();

	void Render(Technique tech, Object obj, const std::vector<glm::mat4>& matrices, Transform transform = {});
	void Render_Ground(const std::vector<glm::mat4>& matrices, const std::vector<GLfloat>& numbers);
	void Render_SkyBox();

protected:
	void Init_Programs();
	void Delete_Programs();
	void Init_Textures();
	void Delete_Textures();
	void Init_Models();
	void Delete_Models();
	void Init_Shapes();
	void Delete_Shapes();

	void Render_Normal(Shape* shape, const Transform& transform);
	void Render_Normal_WireFrame(Shape* shape, const Transform& transform);
	void Render_Instanced(Shape* shape, const std::vector<glm::mat4>& matrices, const Transform& transform);
	void Render_Instanced_WireFrame(Shape* shape, const std::vector<glm::mat4>& matrices, const Transform& transform);

private: 
	Camera* m_Camera;
	ProgramObject* m_InstanceProgram = nullptr;
	ProgramObject* m_RayProgram = nullptr;
	ProgramObject* m_BaseProgram = nullptr;
	ProgramObject* m_SkyBoxProgram = nullptr;
	Texture2D* t_Texture = nullptr;
	FrameBuffer* m_FrameBuffer = nullptr;
	TextureMap* t_TextureSkybox = nullptr;

	Model* m_Model = nullptr;
	Cube* r_Cube = nullptr;
	Cone* r_Cone = nullptr;
	Sphere* r_Sphere = nullptr;
	Pyramid* r_Pyramid = nullptr;
	Cylinder* r_Cylinder = nullptr;

	Skybox* r_Skybox = nullptr;
	Ground* r_Ground = nullptr;
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
	Tree* r_Tree = nullptr;
	WindTurbine* r_Turbine = nullptr;
	WindTurbinePropeller* r_TurbinePropeller = nullptr;
};