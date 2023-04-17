#include "Renderer.h"

Renderer::Renderer(Camera* camera) :
	m_Camera(camera)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	Init_Textures();
	Init_Programs();
	Init_Models();
	Init_Shapes();

	m_FrameBuffer = new FrameBuffer((int)m_Camera->Get_Width(), (int)m_Camera->Get_Height());
	m_Window_Width = (int)m_Camera->Get_Width();
	m_Window_Height = (int)m_Camera->Get_Height();
}
Renderer::~Renderer()
{
	Delete_Programs();
	Delete_Textures();
	Delete_Models();
	Delete_Shapes();
	delete m_FrameBuffer;
}

//--------------------------------------|Engine|--------------------------------------//

void Renderer::Init_Programs()
{
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

	m_BaseProgram = new ProgramObject();
	m_BaseProgram->Initialize
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

	m_SkyBoxProgram = new ProgramObject();
	m_SkyBoxProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/SkyBox.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/SkyBox.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
		}
		);
}

void Renderer::Delete_Programs()
{
	delete m_InstanceProgram;
	delete m_BaseProgram;
	delete m_RayProgram;
	delete m_SkyBoxProgram;
}

void Renderer::Init_Textures()
{

	t_Texture = new Texture2D();
	t_Texture->LoadTexture("Engine/Renderer/Assets/Textures/Texture.png");

	t_TextureSkybox = new TextureMap();
	t_TextureSkybox->LoadTexture
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
}

void Renderer::Delete_Textures()
{
	delete t_Texture;
	delete t_TextureSkybox;
}

//--------------------------------------|General|--------------------------------------//

void Renderer::Render_Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
}

void Renderer::Render_PreRender(bool changed)
{
	this->changed = changed;

	m_FrameBuffer->Bind();
	m_Camera->Set_ProjMatrix(m_FrameBuffer->Get_FrameWidth(), m_FrameBuffer->Get_FrameHeight());
	Render_Clear();

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseTexture", 1);
	m_InstanceProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_InstanceProgram->SetUniformTexture("u_SpriteTexture", 0, t_Texture); //Upload only once per render calls
	m_InstanceProgram->UnBind();
}

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

//----------------------------------------------------------|Models|----------------------------------------------------------//
//----------------------------------------------------------|Models|----------------------------------------------------------//
//----------------------------------------------------------|Models|----------------------------------------------------------//

void Renderer::Init_Models()
{
	m_Model = new Model("Engine/Renderer/Assets/Objects/Character.obj");
}

void Renderer::Delete_Models()
{
	delete m_Model;
}
/*
void Renderer::RenderInstanced_Model(Model* model, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0) return;

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_InstanceProgram->SetUniform("u_UseTexture", 1);
	m_InstanceProgram->SetUniform("u_M", glm::translate(glm::vec3(0, 0, 0)));

	m_InstanceProgram->SetUniform("u_eye", m_Camera->Get_CameraEye());

	m_Model->RenderInstanced(m_InstanceProgram, transforms);

	m_InstanceProgram->UnBind();
}

void Renderer::RenderInstanced_Character(const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0) return;

	RenderInstanced_Model(m_Model, transforms);
}
*/

//----------------------------------------------------------|Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Shapes|----------------------------------------------------------//

void Renderer::Init_Shapes()
{
	unsigned int buffer_size = 2500;

	r_Skybox = new Skybox();
	r_Skybox->CreateBuffers();

	r_Cube = new Cube();
	r_Cube->CreateBuffers(buffer_size);
	r_Cone = new Cone();
	r_Cone->CreateBuffers(buffer_size);
	r_Sphere = new Sphere();
	r_Sphere->CreateBuffers(buffer_size);
	r_Pyramid = new Pyramid();
	r_Pyramid->CreateBuffers(buffer_size);
	r_Cylinder = new Cylinder();
	r_Cylinder->CreateBuffers(buffer_size);
	r_Residence1 = new ResidenceBuilding1();
	r_Residence1->CreateBuffers(buffer_size);
	r_Residence2 = new ResidenceBuilding2();
	r_Residence2->CreateBuffers(buffer_size);
	r_Residence3 = new ResidenceBuilding3();
	r_Residence3->CreateBuffers(buffer_size);
	r_Industry1 = new IndustryBuilding1();
	r_Industry1->CreateBuffers(buffer_size);
	r_Industry2 = new IndustryBuilding2();
	r_Industry2->CreateBuffers(buffer_size);
	r_Industry3 = new IndustryBuilding3();
	r_Industry3->CreateBuffers(buffer_size);
	r_Service1 = new ServiceBuilding1();
	r_Service1->CreateBuffers(buffer_size);
	r_Service2 = new ServiceBuilding2();
	r_Service2->CreateBuffers(buffer_size);
	r_Service3 = new ServiceBuilding3();
	r_Service3->CreateBuffers(buffer_size);
	r_School1 = new SchoolBuilding1();
	r_School1->CreateBuffers(buffer_size);
	r_School2 = new SchoolBuilding2();
	r_School2->CreateBuffers(buffer_size);
	r_PowerStation = new PowerBuilding();
	r_PowerStation->CreateBuffers(buffer_size);
	r_PowerWire = new PowerWireBuilding();
	r_PowerWire->CreateBuffers(buffer_size);
	r_PowerStationPlinth = new PowerBuildingPlinth();
	r_PowerStationPlinth->CreateBuffers(buffer_size);
	r_FireStation = new FireBuilding();
	r_FireStation->CreateBuffers(buffer_size);
	r_PoliceStation = new PoliceBuilding();
	r_PoliceStation->CreateBuffers(buffer_size);
	r_Stadion = new StadionBuilding();
	r_Stadion->CreateBuffers(buffer_size);
	r_Tree = new Tree();
	r_Tree->CreateBuffers(buffer_size);
	r_Turbine = new WindTurbine();
	r_Turbine->CreateBuffers(buffer_size);
	r_TurbinePropeller = new WindTurbinePropeller();
	r_TurbinePropeller->CreateBuffers(buffer_size);
	r_Ground = new Ground();
	r_Ground->CreateBuffers(buffer_size);

	r_Meteor = new Shape_Meteor();
	r_Meteor->CreateBuffers(2500);
}

void Renderer::Delete_Shapes()
{
	delete r_Skybox;
	delete r_Cube;
	delete r_Cone;
	delete r_Sphere;
	delete r_Pyramid;
	delete r_Cylinder;
	delete r_Residence1;
	delete r_Residence2;
	delete r_Residence3;
	delete r_Industry1;
	delete r_Industry2;
	delete r_Industry3;
	delete r_Service1;
	delete r_Service2;
	delete r_Service3;
	delete r_School1;
	delete r_School2;
	delete r_PowerStation;
	delete r_PowerWire;
	delete r_PowerStationPlinth;
	delete r_FireStation;
	delete r_PoliceStation;
	delete r_Stadion;
	delete r_Ground;
	delete r_Tree;
	delete r_Turbine;
	delete r_Meteor;
}

void Renderer::Render(Technique tech, Object obj, const std::vector<glm::mat4>& matrices, Transform transform)
{
	bool deactivate = !changed;

	Shape* shape = nullptr;
	
	switch (obj) 
	{
	case R_RESIDENTIAL_LVL1: shape = r_Residence1; break;
	case R_RESIDENTIAL_LVL2: shape = r_Residence2; break;
	case R_RESIDENTIAL_LVL3: shape = r_Residence3; break;
	case R_INDUSTRIAL_LVL1: shape = r_Industry1; break;
	case R_INDUSTRIAL_LVL2: shape = r_Industry2; break;
	case R_INDUSTRIAL_LVL3: shape = r_Industry3; break;
	case R_SERVICE_LVL1: shape = r_Service1; break;
	case R_SERVICE_LVL2: shape = r_Service2; break;
	case R_SERVICE_LVL3: shape = r_Service3; break;
	case R_FOREST: shape = r_Tree; break;
	case R_POLICESTATION: shape = r_PoliceStation; break;
	case R_FIRESTATION: shape = r_FireStation; break;
	case R_HIGHSCHOOL: shape = r_School1 ; break;
	case R_UNIVERSITY: shape = r_School2; break;
	case R_STADIUM:	shape = r_Stadion; break;
	case R_WINDTURBINE: shape = r_Turbine; break;
	case R_WINDTURBINE_PROPELLER: shape = r_TurbinePropeller; break;
	case R_POWERWIRE: shape = r_PowerWire; break;
	case R_METEOR: shape = r_Meteor; changed = true; break;
	}

	switch (tech)
	{
	case NORMAL:
		Render_Normal(shape, transform);
		break;
	case NORMAL_WIREFRAME:
		Render_Normal_WireFrame(shape, transform);
		break;
	case INSTANCED: 
		Render_Instanced(shape, matrices, transform);
		break;
	case INSTANCED_WIREFRAME:
		Render_Instanced_WireFrame(shape, matrices, transform);
		break;
	}

	if (deactivate) changed = false;
}

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

void Renderer::Render_Normal_WireFrame(Shape* shape, const Transform& transform)
{
	if (shape == nullptr) return;

	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Render_Normal(shape, transform);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}

void Renderer::Render_Instanced(Shape* shape, const std::vector<glm::mat4>& matrices, const Transform& transform)
{
	if (shape == nullptr) return;
	if (matrices.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseVertexTexID", (float)(shape == r_Ground));
	m_InstanceProgram->SetUniform("u_eye", m_Camera->Get_CameraEye());

	m_InstanceProgram->SetUniform("u_LightDir", r_LightProperties.lightDir);
	m_InstanceProgram->SetUniform("u_Specular_Pow", r_LightProperties.specularPow);
	m_InstanceProgram->SetUniform("u_La", r_LightProperties.La);
	m_InstanceProgram->SetUniform("u_Ld", r_LightProperties.Ld);
	m_InstanceProgram->SetUniform("u_Ls", r_LightProperties.Ls);
	m_InstanceProgram->SetUniform("u_Ka", r_LightProperties.Ka);
	m_InstanceProgram->SetUniform("u_Kd", r_LightProperties.Kd);
	m_InstanceProgram->SetUniform("u_Ks", r_LightProperties.Ks);

	shape->Bind();
	if (changed) shape->AttachMatricesSubData(matrices);

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		Transform tf;
		tf.translate = transform.translate * shape->Get_Transforms()[i].translate;
		tf.rotate = transform.rotate * shape->Get_Transforms()[i].rotate;
		tf.scale = transform.scale * shape->Get_Transforms()[i].scale;

		m_InstanceProgram->SetUniform("u_M", Transform::MultiplyTransformMatrices(tf));
		shape->RenderInstanced();
	}

	shape->UnBind();
	m_InstanceProgram->UnBind();
}

void Renderer::Render_Instanced_WireFrame(Shape* shape, const std::vector<glm::mat4>& transforms, const Transform& transform)
{
	if (shape == nullptr) return;

	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Render_Instanced(shape, transforms, transform);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
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