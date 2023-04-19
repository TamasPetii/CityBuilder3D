#include "Renderer.h"

bool Renderer::Buildable = false;
bool Renderer::Changed = false;
Camera*        Renderer::m_Camera;
Skybox*        Renderer::m_Skybox;
Ground*        Renderer::m_Ground;
Shape_Meteor*  Renderer::m_Meteor;
std::vector<glm::mat4> Renderer::GroundTransforms;
std::vector<GLfloat> Renderer::GroundTexturesID;
ProgramObject* Renderer::m_InstanceProgram;
ProgramObject* Renderer::m_NormalProgram;
ProgramObject* Renderer::m_RayProgram;
ProgramObject* Renderer::m_SkyboxProgram;
FrameBuffer*   Renderer::m_FrameBuffer;
Texture2D*     Renderer::m_GameTexture;
TextureMap*    Renderer::m_SkyboxTexture;
std::unordered_map<RenderShapeType, std::pair<Shape*, std::vector<glm::mat4>>> Renderer::m_ShapeData;

void Renderer::Init(Camera* camera)
{
	//[OPENGL]------------------------------------------------------------------------------------//
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	
	//[PROGRAM_OBJECTS]---------------------------------------------------------------------------//
	m_InstanceProgram = new ProgramObject();
	m_InstanceProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Instance.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Instance.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
			ShaderObjectLayout(1, "vert_normal"),
			ShaderObjectLayout(2, "vert_texture"),
			ShaderObjectLayout(3, "vert_textureID"),
			ShaderObjectLayout(4, "vert_id"),
			ShaderObjectLayout(5, "vert_transforms")
		}
		);

	m_NormalProgram = new ProgramObject();
	m_NormalProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Base.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Base.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
			ShaderObjectLayout(1, "vert_normal"),
			ShaderObjectLayout(2, "vert_texture"),
			ShaderObjectLayout(3, "vert_matrix")
		}
		);

	m_RayProgram = new ProgramObject();
	m_RayProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Ray.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Ray.frag")
		},
		{
		}
		);

	m_SkyboxProgram = new ProgramObject();
	m_SkyboxProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/SkyBox.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/SkyBox.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
		}
	);

	//[TEXTURES]---------------------------------------------------------------------------//

	m_GameTexture = new Texture2D();
	m_GameTexture->LoadTexture("Engine/Renderer/Assets/Textures/Texture.png");

	m_SkyboxTexture = new TextureMap();
	m_SkyboxTexture->LoadTexture
	(
		{
		"Engine/Renderer/Assets/Textures/Skybox/right.jpg",
		"Engine/Renderer/Assets/Textures/Skybox/left.jpg",
		"Engine/Renderer/Assets/Textures/Skybox/top.jpg",
		"Engine/Renderer/Assets/Textures/Skybox/bottom.jpg",
		"Engine/Renderer/Assets/Textures/Skybox/front.jpg",
		"Engine/Renderer/Assets/Textures/Skybox/back.jpg"
		}
	);

	//[VIEWPORT]---------------------------------------------------------------------------//

	m_Camera = camera;
	m_FrameBuffer = new FrameBuffer((int)m_Camera->Get_Width(), (int)m_Camera->Get_Height());

	//[SHAPES]---------------------------------------------------------------------------//

	m_Skybox = new Skybox();
	m_Skybox->CreateBuffers();

	m_Ground = new Ground();
	m_Ground->CreateBuffers(5000);

	m_Meteor = new Shape_Meteor();
	m_Meteor->CreateBuffers(2500);

	m_ShapeData[RENDER_RESIDENTIAL_LVL1] = std::make_pair(new ResidenceBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL2] = std::make_pair(new ResidenceBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL3] = std::make_pair(new ResidenceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL1]  = std::make_pair(new IndustryBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL2]  = std::make_pair(new IndustryBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL3]  = std::make_pair(new IndustryBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL1]     = std::make_pair(new ServiceBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL2]     = std::make_pair(new ServiceBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL3]     = std::make_pair(new ServiceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_FOREST]           = std::make_pair(new Tree(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_POLICESTATION]    = std::make_pair(new PoliceBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_FIRESTATION]      = std::make_pair(new FireBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_HIGHSCHOOL]       = std::make_pair(new SchoolBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_UNIVERSITY]       = std::make_pair(new SchoolBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_STADIUM]          = std::make_pair(new StadionBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_POWERWIRE]        = std::make_pair(new PowerWireBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_WINDTURBINE]      = std::make_pair(new WindTurbine(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_WINDTURBINE_PROPELLER] = std::make_pair(new WindTurbinePropeller(), std::vector<glm::mat4>());

	ResizeShapeBuffer(50000);
}

void Renderer::Destroy()
{
	delete  m_InstanceProgram;
	delete  m_NormalProgram;
	delete  m_RayProgram;
	delete  m_SkyboxProgram;
	delete  m_GameTexture;
	delete  m_SkyboxTexture;
	delete  m_FrameBuffer;
}

void Renderer::PreRender()
{
	m_FrameBuffer->Bind();
	m_Camera->Set_ProjMatrix(m_FrameBuffer->Get_FrameWidth(), m_FrameBuffer->Get_FrameHeight());

	ClearScene();

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseTexture", 1);
	m_InstanceProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_InstanceProgram->SetUniform("u_eye", m_Camera->Get_CameraEye());
	m_InstanceProgram->SetUniformTexture("u_SpriteTexture", 0, m_GameTexture);
	m_InstanceProgram->UnBind();

	m_NormalProgram->Bind();
	m_NormalProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_NormalProgram->SetUniformTexture("u_SpriteTexture", 0, m_GameTexture);
	m_NormalProgram->UnBind();
}

void Renderer::PostRender()
{
	m_FrameBuffer->UnBind();
	ClearShapeTransforms();
	Changed = false;
}

void Renderer::SceneRender(RenderMode mode)
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		if (mode == INSTANCED) RenderInstanced((*it).second.first, (*it).second.second);
		if (mode == INSTANCED_WIREFRAME) RenderInstanced_Wireframe((*it).second.first, (*it).second.second);
	}

	Render_Meteors();
	RenderInstancedGround();
	Render_Skybox();
}

void Renderer::RenderInstanced(Shape* shape, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseVertexTexID", (float)(shape == m_Ground));

	shape->Bind();
	if (Changed)
	{
		shape->AttachMatricesSubData(transforms);
	}
	shape->RenderInstanced();
	shape->UnBind();

	m_InstanceProgram->UnBind();
}

void Renderer::RenderInstanced_Wireframe(Shape* shape, const std::vector<glm::mat4>& transforms)
{

	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	RenderInstanced(shape, transforms);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}


void Renderer::ClearScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
}


void Renderer::ClearShapeTransforms()
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.second.clear();
	}

	GroundTransforms.clear();
	GroundTexturesID.clear();
}

void Renderer::ResizeShapeBuffer(int buffer_size)
{
	//TODO!!!
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.first->CreateBuffers(buffer_size);
	}
}

void Renderer::AddShapeTransforms(RenderShapeType type, int x, int y, int direction, int amount)
{
	if (m_ShapeData.find(type) == m_ShapeData.end()) return;

	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(M_PI / 2 * direction, glm::vec3(0, 1, 0));
	transform_MAJOR.scale = glm::mat4(1); //TODO: 2x2 field

	for (int i = 0; i < m_ShapeData[type].first->Get_Transforms().size() && i < amount; i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = m_ShapeData[type].first->Get_Transforms()[i].translate;
		transform_MINOR.rotate = m_ShapeData[type].first->Get_Transforms()[i].rotate; //TODO: Dynamic
		transform_MINOR.scale = m_ShapeData[type].first->Get_Transforms()[i].scale;

		m_ShapeData[type].second.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
	}
}

void Renderer::Set_LightProperties(const LightProperties& LightProperties)
{
	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_LightDir", LightProperties.lightDir);
	m_InstanceProgram->SetUniform("u_Specular_Pow", LightProperties.specularPow);
	m_InstanceProgram->SetUniform("u_La", LightProperties.La);
	m_InstanceProgram->SetUniform("u_Ld", LightProperties.Ld);
	m_InstanceProgram->SetUniform("u_Ls", LightProperties.Ls);
	m_InstanceProgram->SetUniform("u_Ka", LightProperties.Ka);
	m_InstanceProgram->SetUniform("u_Kd", LightProperties.Kd);
	m_InstanceProgram->SetUniform("u_Ks", LightProperties.Ks);
	m_InstanceProgram->UnBind();
}

void Renderer::Render_Skybox()
{
	m_SkyboxProgram->Bind();
	m_SkyboxProgram->SetUniform("u_UseTexture", 1);
	m_SkyboxProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_SkyboxProgram->SetUniform("u_M", glm::translate(m_Camera->Get_CameraEye()));
	m_SkyboxProgram->SetUniformTexture("u_textureMap", 0, m_SkyboxTexture);

	m_Skybox->Render();

	m_SkyboxProgram->UnBind();
}

void Renderer::AddGroundTransforms(int x, int y, int texture)
{
	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(M_PI / 2 * (texture / 100), glm::vec3(0,1,0));
	transform_MAJOR.scale = glm::mat4(1); //TODO SCALE

	for (int i = 0; i < m_Ground->Get_Transforms().size(); i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = m_Ground->Get_Transforms()[i].translate;
		transform_MINOR.rotate = m_Ground->Get_Transforms()[i].rotate; //TODO: Dynamic
		transform_MINOR.scale = m_Ground->Get_Transforms()[i].scale;

		//TODO -> ONLY ONCE
		GroundTransforms.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
	}

	GroundTexturesID.push_back((GLfloat)(texture % 100));
}

void Renderer::RenderInstancedGround()
{
	if (Changed)
	{
		m_Ground->Bind();
		m_Ground->AttachNumbersSubData(GroundTexturesID);
		m_Ground->UnBind();
	}

	RenderInstanced(m_Ground, GroundTransforms);
}

int Renderer::DetermineGroundTextureID(RenderShapeType type)
{
	switch (type)
	{
	case RENDER_RESIDENTIAL_LVL1: return 8;
	case RENDER_RESIDENTIAL_LVL2: return 8;
	case RENDER_RESIDENTIAL_LVL3: return 8;
	case RENDER_INDUSTRIAL_LVL1: return 12;
	case RENDER_INDUSTRIAL_LVL2: return 12;
	case RENDER_INDUSTRIAL_LVL3: return 12;
	case RENDER_SERVICE_LVL1: return 10;
	case RENDER_SERVICE_LVL2: return 10;
	case RENDER_SERVICE_LVL3: return 10;
	case RENDER_FOREST: return 1;
	case RENDER_POLICESTATION: return 15;
	case RENDER_FIRESTATION: return 15;
	case RENDER_HIGHSCHOOL: return 14;
	case RENDER_UNIVERSITY: return 14;
	case RENDER_STADIUM: return 11;
	case RENDER_POWERWIRE: return 63;
	case RENDER_WINDTURBINE: return 2;
	case RENDER_EMPTY: return 0;
	case RENDER_CRATER: return 49;
	}
}

void Renderer::Render_Meteors()
{
	bool not_changed = !Changed;
	Changed = true;

	RenderInstanced(m_Meteor, MeteorGrp::Get_Transforms());

	if (not_changed) Changed = false;
}

void Renderer::RenderNormal(RenderShapeType type, int x, int y, int direction)
{
	if (m_ShapeData.find(type) == m_ShapeData.end()) return;

	Shape* shape = m_ShapeData[type].first;

	m_NormalProgram->Bind();
	m_NormalProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());

	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(M_PI / 2 * direction, glm::vec3(0, 1, 0));
	transform_MAJOR.scale = glm::mat4(1); //TODO SCALE

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = shape->Get_Transforms()[i].translate;
		transform_MINOR.rotate = shape->Get_Transforms()[i].rotate;
		transform_MINOR.scale = shape->Get_Transforms()[i].scale;

		m_NormalProgram->SetUniform("u_M", Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
		m_NormalProgram->SetUniform("u_color", Buildable ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0));

		shape->Bind();
		shape->Render();
		shape->UnBind();
	}

	m_NormalProgram->UnBind();
}

void Renderer::RenderNormal_Wireframe(RenderShapeType type, int x, int y, int direction)
{
	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	RenderNormal(type, x, y, direction);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}