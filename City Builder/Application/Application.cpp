#include "Application.h"

Application::Application(GLFWwindow* window, int WINDOW_WIDTH, int WINDOW_HEIGHT)
	:
	m_Window(window),
	m_WindowWidth(WINDOW_WIDTH),
	m_WindowHeight(WINDOW_HEIGHT)
{

	m_Camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_City = new City(50);
	m_Renderer = new Renderer(m_Camera);
	m_MyGui = new MyGui(m_Camera);
	m_FrameCounter = new FrameCounter();
	m_Timer = new Timer(0.5);
	m_Timer->Start();

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));
}

Application::~Application()
{
	delete m_Camera;
	delete m_Renderer;
	delete m_MyGui;
	delete m_City;
}

void Application::Update()
{
	m_Timer->Update();
	m_FrameCounter->Update();
	m_Camera->Update();

	if (m_Timer->Tick())
	{
		std::cout << "TIMER TICK" << std::endl;
	}

	if (m_FrameCounter->Tick())
	{
		std::cout << m_FrameCounter->Get_FPS() << std::endl;
		m_FrameCounter->Reset();
	}

	//------------------------------

	if (m_MyGui->hit)
	{
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, m_Renderer->Get_FrameBuffer()->Get_FrameWidth(), m_Renderer->Get_FrameBuffer()->Get_FrameHeight());
		m_MyGui->hit = false;
	}
}

void Application::RenderUI()
{
	m_MyGui->Pre_Render();

	m_MyGui->DockSpace_Render();
	m_MyGui->Demo_Render();
	m_MyGui->Window1_Render();
	m_MyGui->Window2_Render();
	m_MyGui->Window3_Render();
	m_MyGui->Window4_Render();
	m_MyGui->Window5_Render();
	m_MyGui->ViewPort_Render(m_Renderer->Get_FrameBuffer());

	m_MyGui->Post_Render();
}

void Application::Render()
{
	if (changed)
	{
		std::cout << "CHANGED" << std::endl;
		for (int i = 0; i < m_City->Get_GameTableSize(); i++)
		{
			for (int j = 0; j < m_City->Get_GameTableSize(); j++)
			{
				Transform transform;
				transform.translate = glm::translate(glm::vec3(2 * j + 1, 0, 2 * i + 1));

				transforms_GROUND.push_back(Shape::MultiplyTransformMatrices(transform));

				GameField* field = m_City->Get_GameField(i, j);
				if (field->IsEmpty())
				{
					numbers_GROUND.push_back(0);
				}
				else if (field->IsRoad())
				{
					numbers_GROUND.push_back(1);
				}
				else if (field->IsForest())
				{
					transforms_FOREST.push_back(Shape::MultiplyTransformMatrices(transform));
					numbers_GROUND.push_back(40);
				}
				else if (field->IsZone())
				{
					Zone* zone = dynamic_cast<Zone*>(field);
					if (zone->IsResidentalArea()) 
					{
						switch(zone->Get_Level())
						{
						case LEVEL_1: transforms_RESIDENCE1.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(10); break;
						case LEVEL_2: transforms_RESIDENCE2.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(20); break;
						case LEVEL_3: transforms_RESIDENCE3.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(30); break;
						}
					}
					else if (zone->IsWorkingArea()) 
					{
						WorkingArea* area = dynamic_cast<WorkingArea*>(zone);
						if (area->IsIndustrialArea()) 
						{
							switch (area->Get_Level())
							{
							case LEVEL_1: transforms_INDUSTRY1.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(10); break;
							case LEVEL_2: transforms_INDUSTRY2.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(20); break;
							case LEVEL_3: transforms_INDUSTRY3.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(30); break;
							}
						}
						else if (area->IsServiceArea())
						{
							switch (area->Get_Level())
							{
							case LEVEL_1: transforms_SERVICE1.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(10); break;
							case LEVEL_2: transforms_SERVICE2.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(20); break;
							case LEVEL_3: transforms_SERVICE3.push_back(Shape::MultiplyTransformMatrices(transform)); numbers_GROUND.push_back(30); break;
							}
						}
					}
				}
				else if (field->IsBuilding()) 
				{
					Building* building = dynamic_cast<Building*>(field);
					if (building->IsPoliceStation()) 
					{
						transforms_FIRESTATION.push_back(Shape::MultiplyTransformMatrices(transform));
						numbers_GROUND.push_back(50);
					}
					else if (building->IsFireStation()) 
					{
						transforms_POLICESTATION.push_back(Shape::MultiplyTransformMatrices(transform));
						numbers_GROUND.push_back(70);
					}
					else if (building->IsStadium())
					{
						transforms_STADION.push_back(Shape::MultiplyTransformMatrices(transform));
						numbers_GROUND.push_back(50);
					}
					else if (building->IsSchool()) 
					{
						School* school = dynamic_cast<School*>(building);
						if (school->IsHighSchool()) 
						{
							transforms_SCHOOL1.push_back(Shape::MultiplyTransformMatrices(transform));
							numbers_GROUND.push_back(53);
						}
						else if (school->IsUniversity()) 
						{
							transforms_SCHOOL2.push_back(Shape::MultiplyTransformMatrices(transform));
							numbers_GROUND.push_back(63);
						}
					}
					else if (building->IsPowerStation()) 
					{
						transform.rotate = glm::rotate<float>(glm::radians(360.f / 50.f * j), glm::vec3(0, 1, 0));
						transform.scale = glm::scale(glm::vec3(2));
						transforms_POWERSTATION.push_back(Shape::MultiplyTransformMatrices(transform));
						numbers_GROUND.push_back(81);
					}
					else if (building->IsPowerWire())
					{
						transforms_POWERWIRE.push_back(Shape::MultiplyTransformMatrices(transform));
						numbers_GROUND.push_back(83);
					}
				}
			}
		}
	}

	m_Renderer->Render_PreRender(changed);
	
	if (m_MyGui->BuildHover) 
	{
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, (int)m_MyGui->content_size.x, (int)m_MyGui->content_size.y);
		int x = (int)RayHit.x / 2 * 2 + 1;
		int z = (int)RayHit.z / 2 * 2 + 1;

		bool l1 = RayHit.x > 0 && RayHit.x < m_City->Get_GameTableSize() * 2;
		bool l2 = RayHit.z > 0 && RayHit.z < m_City->Get_GameTableSize() * 2;

		if (l1 && l2)
		{
			m_Renderer->buildable = m_City->Get_GameField(RayHit.z / 2, RayHit.x / 2)->IsEmpty();
			Transform tr;
			tr.translate = glm::translate(glm::vec3(x, 0, z));
			tr.rotate = glm::rotate<float>(glm::radians(90.f) * (m_MyGui->r % 4), glm::vec3(0, 1, 0));
			m_Renderer->Render(NORMAL_WIREFRAME, R_INDUSTRIAL_LVL2,  {}, tr);
		}
	}

	m_Renderer->Render_Ground(transforms_GROUND, numbers_GROUND);
	m_Renderer->Render(INSTANCED, R_FOREST,                transforms_FOREST);
	m_Renderer->Render(INSTANCED, R_RESIDENTIAL_LVL1,      transforms_RESIDENCE1);
	m_Renderer->Render(INSTANCED, R_RESIDENTIAL_LVL2,      transforms_RESIDENCE2);
	m_Renderer->Render(INSTANCED, R_RESIDENTIAL_LVL3,      transforms_RESIDENCE3);
	m_Renderer->Render(INSTANCED, R_INDUSTRIAL_LVL1,       transforms_INDUSTRY1);
	m_Renderer->Render(INSTANCED, R_INDUSTRIAL_LVL2,       transforms_INDUSTRY2);
	m_Renderer->Render(INSTANCED, R_INDUSTRIAL_LVL3,       transforms_INDUSTRY3);
	m_Renderer->Render(INSTANCED, R_SERVICE_LVL1,          transforms_SERVICE1);
	m_Renderer->Render(INSTANCED, R_SERVICE_LVL2,          transforms_SERVICE2);
	m_Renderer->Render(INSTANCED, R_SERVICE_LVL3,          transforms_SERVICE3);
	m_Renderer->Render(INSTANCED, R_FIRESTATION,           transforms_FIRESTATION);
	m_Renderer->Render(INSTANCED, R_POLICESTATION,         transforms_POLICESTATION);
	m_Renderer->Render(INSTANCED, R_STADIUM,               transforms_STADION);
	m_Renderer->Render(INSTANCED, R_WINDTURBINE,		   transforms_POWERSTATION);
	m_Renderer->Render(INSTANCED, R_WINDTURBINE_PROPELLER, transforms_POWERSTATION, {glm::mat4(1), glm::rotate<float>(abs(glfwGetTime() * 2 * M_PI), glm::vec3(0, 0, 1)), glm::mat4(1)});
	m_Renderer->Render(INSTANCED, R_POWERWIRE,             transforms_POWERWIRE);
	m_Renderer->Render(INSTANCED, R_HIGHSCHOOL,            transforms_SCHOOL1);
	m_Renderer->Render(INSTANCED, R_UNIVERSITY,            transforms_SCHOOL2);
	m_Renderer->Render_Axis();
	m_Renderer->Render_Ray(RayOrigin, RayHit);
	m_Renderer->Render_SkyBox();
	m_Renderer->Render_PostRender();

	if (changed) 
	{
		changed = false;
		transforms_GROUND.clear();
		numbers_GROUND.clear();

		transforms_CUBE.clear();
		transforms_CONE.clear();
		transforms_CYLINDER.clear();
		transforms_PYRAMID.clear();
		transforms_SPHERE.clear();
		transforms_FOREST.clear();
		transforms_RESIDENCE1.clear();
		transforms_RESIDENCE2.clear();
		transforms_RESIDENCE3.clear();
		transforms_INDUSTRY1.clear();
		transforms_INDUSTRY2.clear();
		transforms_INDUSTRY3.clear();
		transforms_SERVICE1.clear();
		transforms_SERVICE2.clear();
		transforms_SERVICE3.clear();
		transforms_FIRESTATION.clear();
		transforms_POLICESTATION.clear();
		transforms_STADION.clear();
		transforms_POWERSTATION.clear();
		transforms_POWERWIRE.clear();
		transforms_SCHOOL1.clear();
		transforms_SCHOOL2.clear();
		transforms_CHARACTER.clear();
	}
}


//---------------------------------------------------------|Events|---------------------------------------------------------//
//---------------------------------------------------------|Events|---------------------------------------------------------//
//---------------------------------------------------------|Events|---------------------------------------------------------//

void Application::Window_ResizedEvent(int width, int height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;

	m_Renderer->Set_WindowSize(width, height);
};

void Application::FrameBuffer_ResizedEvent(int width, int height)
{
	m_Camera->Set_ProjMatrix(width, height);
};

void Application::ConvertMouseInputTo3D(int xpos, int ypos, int width, int height)
{
	//Turning [x,y] coordinates to Normalized Device Coordinate system [-1,1]
	float xnorm = (xpos / (float)width - 0.5f) * 2.f;
	float ynorm = (ypos / (float)height - 0.5f) * -2.f;

	//[z = -1.] camera starting point in NDC
	//[z = 1.f] the furthest point in NDC
	glm::vec4 startRayNorm(xnorm, ynorm, -1.f, 1.f);
	glm::vec4 endRayNorm(xnorm, ynorm, 1.f, 1.f);

	//We need to go backwards in coordinate systems.
	//NDC -> PROJ -> VIEW -> WORLD
	glm::mat4 matrix = glm::inverse(m_Camera->Get_ViewProjMatrix());
	glm::vec4 startRayWorld = matrix * startRayNorm; startRayWorld /= startRayWorld.w;
	glm::vec4 endRayWorld = matrix * endRayNorm; endRayWorld /= endRayWorld.w;

	RayOrigin = startRayWorld;
	RayEnd = endRayWorld;
	RayDirection = glm::normalize(endRayWorld - startRayWorld);

	/*
	The whole map is at [y = 0.5f] so we need to find that point in the ray which height = 0.5f
	We use the parametric equation to determine the x,y values
	*/

	float t = (0.f - startRayWorld.y) / RayDirection.y;
	RayHit = glm::vec3(RayOrigin.x + t * RayDirection.x, 0.0, RayOrigin.z + t * RayDirection.z);

	/*
	Checking possible ray and field hit.
	If possible then we determine the [x,y] values which represent the indices of the GameField
	*/

	float rayx = RayHit.x;
	float rayz = RayHit.z;

	bool l_1 = rayx > 0.f && rayx < m_City->Get_GameTableSize() * 2 && t >= 0;
	bool l_2 = rayz > 0.f && rayz < m_City->Get_GameTableSize() * 2 && t >= 0;

	if (l_1 && l_2)
	{

		rayx /= 2.f;
		rayz /= 2.f;
	}
}