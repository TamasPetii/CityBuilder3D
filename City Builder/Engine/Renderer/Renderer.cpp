#include "Renderer.h"
/*

//--------------------------------------|General|--------------------------------------//



void Renderer::Render_PostRender()
{
	changed = false;
	m_FrameBuffer->UnBind();
}

void Renderer::Render_Axis()
{
	m_RayProgram->Bind();
	m_RayProgram->SetUniform("u_MVP", m_Camera->Get_ViewProjMatrix());

	r_Cube->Bind();

	m_RayProgram->SetUniform("u_RayStart", glm::vec3(0, 0, 0));
	m_RayProgram->SetUniform("u_RayEnd", glm::vec3(100, 0, 0));
	m_RayProgram->SetUniform("u_Color", glm::vec3(1, 0, 0));
	glDrawArrays(GL_LINES, 0, 2);

	m_RayProgram->SetUniform("u_RayStart", glm::vec3(0, 0, 0));
	m_RayProgram->SetUniform("u_RayEnd", glm::vec3(0, 100, 0));
	m_RayProgram->SetUniform("u_Color", glm::vec3(0, 1, 0));
	glDrawArrays(GL_LINES, 0, 2);

	m_RayProgram->SetUniform("u_RayStart", glm::vec3(0, 0, 0));
	m_RayProgram->SetUniform("u_RayEnd", glm::vec3(0, 0, 100));
	m_RayProgram->SetUniform("u_Color", glm::vec3(0, 0, 1));
	glDrawArrays(GL_LINES, 0, 2);

	r_Cube->UnBind();

	m_RayProgram->UnBind();
}

void Renderer::Render_Ray(const glm::vec3& start, const glm::vec3& end)
{
	m_RayProgram->Bind();
	m_RayProgram->SetUniform("u_MVP", m_Camera->Get_ViewProjMatrix());
	m_RayProgram->SetUniform("u_RayStart", start);
	m_RayProgram->SetUniform("u_RayEnd", end);
	m_RayProgram->SetUniform("u_Color", glm::vec3(1, 1, 0));

	r_Cube->Bind();
	glDrawArrays(GL_LINES, 0, 2);
	r_Cube->UnBind();

	m_RayProgram->UnBind();
}



//----------------------------------------------------------|Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Shapes|----------------------------------------------------------//

void Renderer::Render_Normal(Shape* shape, const Transform& transform)
{
	if (shape == nullptr) return;

	m_BaseProgram->Bind();
	m_BaseProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());

	shape->Bind();

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		Transform tf;
		tf.translate = transform.translate * shape->Get_Transforms()[i].translate;
		tf.rotate = transform.rotate * shape->Get_Transforms()[i].rotate;
		tf.scale = transform.scale * shape->Get_Transforms()[i].scale;

		m_BaseProgram->SetUniform("u_M", Transform::MultiplyTransformMatrices(tf));
		m_BaseProgram->SetUniform("u_color", buildable ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0));
		shape->Render();
	}

	shape->UnBind();
	m_BaseProgram->UnBind();
}



void Renderer::Render_Ground(const std::vector<glm::mat4>& matrices, const std::vector<GLfloat>& numbers)
{
	Shape* shape = r_Ground;

	if (changed)
	{
		shape->Bind();
		shape->AttachNumbersSubData(numbers);
		shape->UnBind();
	}

	Transform t;
	Render_Instanced(r_Ground, matrices, t);
}

void Renderer::Render_SkyBox()
{
	m_SkyBoxProgram->Bind();
	m_SkyBoxProgram->SetUniform("u_UseTexture", 1);
	m_SkyBoxProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_SkyBoxProgram->SetUniform("u_M", glm::translate(m_Camera->Get_CameraEye()));
	m_SkyBoxProgram->SetUniformTexture("u_textureMap", 0, t_TextureSkybox);

	r_Skybox->Render();

	m_SkyBoxProgram->UnBind();
}

void Renderer::Set_Light_Properties(glm::vec3 dir, int spec, glm::vec3 la, glm::vec3 ld, glm::vec3 ls, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks)
{
	r_LightProperties.lightDir = dir;
	r_LightProperties.specularPow = spec;
	r_LightProperties.La = la;
	r_LightProperties.Ld = ld;
	r_LightProperties.Ls = ls;
	r_LightProperties.Ka = ka;
	r_LightProperties.Kd = kd;
	r_LightProperties.Ks = ks;
}

void Renderer::Reset_Light_Properties()
{
	r_LightProperties.lightDir = glm::vec3(1, -1, 1);
	r_LightProperties.specularPow = 64;
	r_LightProperties.La = glm::vec3(0.5, 0.5, 0.5);
	r_LightProperties.Ld = glm::vec3(1, 1, 0.85);
	r_LightProperties.Ls = glm::vec3(1, 1, 1);
	r_LightProperties.Ka = glm::vec3(0.8, 0.8, 0.8);
	r_LightProperties.Kd = glm::vec3(1, 1, 1);
	r_LightProperties.Ks = glm::vec3(0.7, 0.6, 0.6);
}

void Renderer::Render_Meteors()
{
	bool not_changed = !changed;
	changed = true;

	Render_Instanced(r_Meteor, MeteorGrp::Get_Transforms(), {});
	
	if (not_changed) changed = false;
}

*/
bool Renderer::Changed = false;
Camera*        Renderer::m_Camera;
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

	m_ShapeData[RENDER_RESIDENTIAL_LVL1] = std::make_pair(new ResidenceBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL2] = std::make_pair(new ResidenceBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL3] = std::make_pair(new ResidenceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL1]  = std::make_pair(new IndustryBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL2]  = std::make_pair(new IndustryBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL3]  = std::make_pair(new IndustryBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL1]     = std::make_pair(new ServiceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL2]     = std::make_pair(new ServiceBuilding3(), std::vector<glm::mat4>());
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
	m_InstanceProgram->SetUniformTexture("u_SpriteTexture", 0, m_GameTexture);
	m_InstanceProgram->UnBind();
}

void Renderer::PostRender()
{
	m_FrameBuffer->UnBind();
	ClearTransforms();
	Changed = false;
}

void Renderer::SceneRender(RenderMode mode)
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		if (mode == INSTANCED) RenderInstanced((*it).second.first, (*it).second.second);
		if (mode == INSTANCED_WIREFRAME) RenderInstanced_Wireframe((*it).second.first, (*it).second.second);
	}
}

void Renderer::RenderInstanced(Shape* shape, const std::vector<glm::mat4>& transforms)
{
	if(transforms.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();

	shape->Bind();
	if (Changed)
	{
		shape->AttachMatricesSubData(transforms);
		std::cout << "TRANSFORM SIZE >> " << transforms.size() << std::endl;
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

void Renderer::AddTransforms(RenderShapeType type, int x, int y, int direction)
{
	if (!(type >= 0 and type <= 17)) return;

	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(M_PI / 2 * direction, glm::vec3(0, 1, 0));
	transform_MAJOR.scale = glm::mat4(1); //TODO: 2x2 field

	for (int i = 0; i < m_ShapeData[type].first->Get_Transforms().size(); i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = m_ShapeData[type].first->Get_Transforms()[i].translate;
		transform_MINOR.rotate = m_ShapeData[type].first->Get_Transforms()[i].rotate; //TODO: Dynamic
		transform_MINOR.scale = m_ShapeData[type].first->Get_Transforms()[i].scale;

		m_ShapeData[type].second.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
	}
}

void Renderer::ClearScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
}


void Renderer::ClearTransforms()
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.second.clear();
	}
}

void Renderer::ResizeShapeBuffer(int buffer_size)
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.first->CreateBuffers(buffer_size);
	}
}