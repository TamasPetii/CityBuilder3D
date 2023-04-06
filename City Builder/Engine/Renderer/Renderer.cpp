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
	Init_BasicShapes();
	Init_ComplexShapes();

	m_FrameBuffer = new FrameBuffer((int)m_Camera->Get_Width(), (int)m_Camera->Get_Height());
	m_Window_Width = (int)m_Camera->Get_Width();
	m_Window_Height = (int)m_Camera->Get_Height();
}
Renderer::~Renderer()
{
	Delete_Programs();
	Delete_Textures();
	Delete_Models();
	Delete_BasicShapes();
	Delete_ComplexShapes();
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
			ShaderObjectLayout(3, "vert_matrix")
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
	t_Texture->LoadTexture("Engine/Renderer/Assets/Textures/SpriteTextures.png");

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

void Renderer::RenderInstanced_Model(Model* model, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0) return;

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_InstanceProgram->SetUniform("u_UseTexture", 1);
	m_InstanceProgram->SetUniform("u_M", glm::translate(glm::vec3(0, 0, 0)));

	m_Model->RenderInstanced(m_InstanceProgram, transforms);

	m_InstanceProgram->UnBind();
}

void Renderer::RenderInstanced_Character(const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0) return;

	RenderInstanced_Model(m_Model, transforms);
}

//------------------------------------------------------|Basic-Shapes|------------------------------------------------------//
//------------------------------------------------------|Basic-Shapes|------------------------------------------------------//
//------------------------------------------------------|Basic-Shapes|------------------------------------------------------//

void Renderer::Init_BasicShapes()
{
	r_Cube = new Cube();
	r_Cube->CreateBuffers();
	r_Cone = new Cone();
	r_Cone->CreateBuffers();
	r_Sphere = new Sphere();
	r_Sphere->CreateBuffers();
	r_Pyramid = new Pyramid();
	r_Pyramid->CreateBuffers();
	r_Cylinder = new Cylinder();
	r_Cylinder->CreateBuffers();
}

void Renderer::Delete_BasicShapes()
{
	delete r_Cube;
	delete r_Cone;
	delete r_Sphere;
	delete r_Pyramid;
	delete r_Cylinder;
}

void Renderer::RenderInstanced_BasicShape(Shape* shape, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();
	shape->Bind();

	if(changed)
		shape->AttachMatricesSubData(transforms);

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		m_InstanceProgram->SetUniform("u_M", shape->Get_Transforms()[i]);
		shape->RenderInstanced();
	}

	shape->UnBind();

	m_InstanceProgram->UnBind();
}

void Renderer::RenderInstanced_Cube(const glm::mat4& transform, const glm::vec3& color)
{
	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_BaseProgram->Bind();
	m_BaseProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_BaseProgram->SetUniform("u_color", color);
	r_Service3->Bind();

	for (int i = 0; i < r_Service3->Get_Transforms().size(); i++)
	{
		m_BaseProgram->SetUniform("u_M", transform * r_Service3->Get_Transforms()[i]);
		r_Service3->Render();
	}

	r_Service3->UnBind();
	m_BaseProgram->UnBind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}

void RenderInstanced_Cone(const std::vector<glm::mat4>& transforms)
{
	//...
}

void RenderInstanced_Sphere(const std::vector<glm::mat4>& transforms)
{
	//...
}

void RenderInstanced_Pyramid(const std::vector<glm::mat4>& transforms)
{
	//...
}

void RenderInstanced_Cylinder(const std::vector<glm::mat4>& transforms)
{
	//...
}

//----------------------------------------------------------|Complex-Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Complex-Shapes|----------------------------------------------------------//
//----------------------------------------------------------|Complex-Shapes|----------------------------------------------------------//

void Renderer::Init_ComplexShapes()
{
	r_Residence1 = new ResidenceBuilding1();
	r_Residence1->CreateBuffers();
	r_Residence2 = new ResidenceBuilding2();
	r_Residence2->CreateBuffers();
	r_Residence3 = new ResidenceBuilding3();
	r_Residence3->CreateBuffers();
	r_Industry1 = new IndustryBuilding1();
	r_Industry1->CreateBuffers();
	r_Industry2 = new IndustryBuilding2();
	r_Industry2->CreateBuffers();
	r_Industry3 = new IndustryBuilding3();
	r_Industry3->CreateBuffers();
	r_Service1 = new ServiceBuilding1();
	r_Service1->CreateBuffers();
	r_Service2 = new ServiceBuilding2();
	r_Service2->CreateBuffers();
	r_Service3 = new ServiceBuilding3();
	r_Service3->CreateBuffers();
	r_School1 = new SchoolBuilding1();
	r_School1->CreateBuffers();
	r_School2 = new SchoolBuilding2();
	r_School2->CreateBuffers();
	r_PowerStation = new PowerBuilding();
	r_PowerStation->CreateBuffers();
	r_PowerWire = new PowerWireBuilding();
	r_PowerWire->CreateBuffers();
	r_PowerStationPlinth = new PowerBuildingPlinth();
	r_PowerStationPlinth->CreateBuffers();
	r_FireStation = new FireBuilding();
	r_FireStation->CreateBuffers();
	r_PoliceStation = new PoliceBuilding();
	r_PoliceStation->CreateBuffers();
	r_Stadion = new StadionBuilding();
	r_Stadion->CreateBuffers();
	r_Ground = new Ground();
	r_Ground->CreateBuffers();
	r_Tree = new Tree();
	r_Tree->CreateBuffers();
}

void Renderer::Delete_ComplexShapes()
{
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
}

void Renderer::RenderInstanced_ComplexShape(Shape* shape, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();
	shape->Bind();

	if (changed)
	{
		shape->AttachMatricesSubData(transforms);
	}

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		m_InstanceProgram->SetUniform("u_M", shape->Get_Transforms()[i]);
		shape->RenderInstanced();
	}

	shape->UnBind();
	m_InstanceProgram->UnBind();
}

void Renderer::RenderInstanced_Residence1(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Residence1, transforms);
}

void Renderer::RenderInstanced_Residence2(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Residence2, transforms);
}

void Renderer::RenderInstanced_Residence3(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Residence3, transforms);
}

void  Renderer::RenderInstanced_Industry1(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Industry1, transforms);
}

void  Renderer::RenderInstanced_Industry2(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Industry2, transforms);
}
void  Renderer::RenderInstanced_Industry3(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Industry3, transforms);
}

void Renderer::RenderInstanced_Service1(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Service1, transforms);
}

void Renderer::RenderInstanced_Service2(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Service2, transforms);
}

void Renderer::RenderInstanced_Service3(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Service3, transforms);
}

void Renderer::RenderInstanced_FireStation(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_FireStation, transforms);
}

void Renderer::RenderInstanced_PoliceStation(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_PoliceStation, transforms);
}

void Renderer::RenderInstanced_PowerStation(const std::vector<glm::mat4>& transforms)
{

	RenderInstanced_ComplexShape(r_PowerStation, transforms);

	//Render only lines not triangles -> transparent affact
	glDisable(GL_CULL_FACE);
	glLineWidth(5.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	RenderInstanced_ComplexShape(r_PowerStationPlinth, transforms);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2.0f);
	glEnable(GL_CULL_FACE);
}

void Renderer::RenderInstanced_PowerWire(const std::vector<glm::mat4>& transforms)
{

}

void Renderer::RenderInstanced_Stadion(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Stadion, transforms);
}

void Renderer::RenderInstanced_School1(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_School1, transforms);
}

void Renderer::RenderInstanced_School2(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_School2, transforms);
}

void Renderer::RenderInstanced_Forest(const std::vector<glm::mat4>& transforms)
{
	RenderInstanced_ComplexShape(r_Tree, transforms);
}

void Renderer::RenderInstanced_Empty(const std::vector<glm::mat4>& transforms)
{

}

void Renderer::RenderInstanced_Road(const std::vector<glm::mat4>& transforms)
{

}