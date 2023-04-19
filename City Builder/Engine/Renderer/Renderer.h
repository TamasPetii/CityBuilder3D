#pragma once

#define _USE_MATH_DEFINES

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
#include <unordered_map>
#include <utility>

struct LightProperties;
enum RenderShapeType;
enum RenderMode;

class Renderer
{
public:
	static bool Changed;
	static bool Buildable;

	static void Init(Camera* camera);
	static void Destroy();

	static void ResizeShapeBuffer(int buffer_size);
	static void AddShapeTransforms(RenderShapeType type, int x, int y, int direction);
	static void AddGroundTransforms(int x, int y, int texture);
	static void ClearShapeTransforms();
	static int  DetermineGroundTextureID(RenderShapeType type);

	static void PreRender();
	static void SceneRender(RenderMode mode);
	static void PostRender();
	static void ClearScene();

	static void Set_LightProperties(const LightProperties& LightProperties);
	static inline FrameBuffer* Get_FrameBuffer() { return m_FrameBuffer; }

	static void RenderNormal(RenderShapeType type, int x, int y);
	static void RenderNormal_Wireframe(RenderShapeType type, int x, int y);
	static void RenderInstanced(Shape* shape, const std::vector<glm::mat4>& transforms);
	static void RenderInstanced_Wireframe(Shape* shape, const std::vector<glm::mat4>& transforms);
protected:

	static void RenderInstancedGround();
	static void Render_Meteors();
	static void Render_Skybox();
private:
	static Ground* m_Ground;
	static std::vector<glm::mat4> GroundTransforms;
	static std::vector<GLfloat> GroundTexturesID;
	static Shape_Meteor* m_Meteor;

	static Camera* m_Camera;
	static Skybox* m_Skybox;
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
	RENDER_EMPTY,
	RENDER_ROAD,
	RENDER_CRATER,
	RENDER_WINDTURBINE_PROPELLER
};

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