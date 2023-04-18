#pragma once

#define _USE_MATH_DEFINES

#define CHECK_EMPTY(x) if(x == 0) return;

//Abstractions
#include "../Abstractions/Model.h"
#include "../Utilities/Camera.h"
#include "../Abstractions/FrameBuffer.h"
#include "../Abstractions/BufferObject.h"
#include "../Abstractions/VertexArrayObject.h"

//Shapes
#include "../Shapes/Basic Shapes/BasicShapes.h"
#include "../Shapes/Complex Shapes/ComplexShape.h"

#include "Utilities/Skybox.h"
#include "Utilities/Meteor.h"

#include <cmath>
#include <list>

//#include "RenderTransforms.h"
//#include "RenderShapes.h"

struct LightProperties
{
	glm::vec3 lightDir = glm::vec3(1, -1, 1);
	int specularPow = 64;
	glm::vec3 La = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 Ld = glm::vec3(1, 1, 0.85);
	glm::vec3 Ls = glm::vec3(1, 1, 1);
	glm::vec3 Ka = glm::vec3(0.8, 0.8, 0.8);
	glm::vec3 Kd = glm::vec3(1, 1, 1);
	glm::vec3 Ks = glm::vec3(0.7, 0.6, 0.6);

};

/*

class asd 
{
public:
	Renderer(Camera* camera);
	~Renderer();
public:
	void Render_Meteors();



	FrameBuffer* Get_FrameBuffer() { return m_FrameBuffer; }

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

	void Set_Light_Properties(glm::vec3 dir, int spec, glm::vec3 la, glm::vec3 ld, glm::vec3 ls, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks);
	void Reset_Light_Properties();


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

	Skybox* r_Skybox = nullptr;
	LightProperties r_LightProperties;
};
*/

#include <unordered_map>
#include <utility>

enum RenderShapeType;
enum RenderMode;

class Renderer
{
public:
	static bool Changed;

	static void Init(Camera* camera);
	static void Destroy();

	static void ResizeShapeBuffer(int buffer_size);
	static void AddTransforms(RenderShapeType type, int x, int y, int direction);
	static void ClearTransforms();

	static void ClearScene();

	static void PreRender();
	static void SceneRender(RenderMode mode);
	static void PostRender();

	static FrameBuffer* Get_FrameBuffer() { return m_FrameBuffer; }
protected:
	static void RenderInstanced(Shape* shape, const std::vector<glm::mat4>& transforms);
	static void RenderInstanced_Wireframe(Shape* shape, const std::vector<glm::mat4>& transforms);
private:
	static Camera* m_Camera;
	static ProgramObject* m_InstanceProgram;
	static ProgramObject* m_NormalProgram;
	static ProgramObject* m_RayProgram;
	static ProgramObject* m_SkyboxProgram;
	static FrameBuffer* m_FrameBuffer;
	static Texture2D* m_GameTexture;
	static TextureMap* m_SkyboxTexture;
	static std::unordered_map<RenderShapeType, std::pair<Shape*, std::vector<glm::mat4>>> m_ShapeData;
};

enum RenderMode
{
	INSTANCED,
	INSTANCED_WIREFRAME,
	NORMAL,
	NORMAL_WIREFRAME
};

enum RenderShapeType
{
	RENDER_RESIDENTIAL_LVL1,
	RENDER_RESIDENTIAL_LVL2,
	RENDER_RESIDENTIAL_LVL3,
	RENDER_INDUSTRIAL_LVL1,
	RENDER_INDUSTRIAL_LVL2,
	RENDER_INDUSTRIAL_LVL3,
	RENDER_SERVICE_LVL1,
	RENDER_SERVICE_LVL2,
	RENDER_SERVICE_LVL3,
	RENDER_FOREST,
	RENDER_POLICESTATION,
	RENDER_FIRESTATION,
	RENDER_HIGHSCHOOL,
	RENDER_UNIVERSITY,
	RENDER_STADIUM,
	RENDER_POWERWIRE,
	RENDER_WINDTURBINE,
	RENDER_WINDTURBINE_PROPELLER
};