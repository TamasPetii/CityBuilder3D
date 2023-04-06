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
	m_Camera->Update();

	//------------------------------

	if (m_MyGui->hit)
	{
		std::cout << "---------FROM APPLICATION--------" << std::endl;
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, (int)m_MyGui->content_size.x, (int)m_MyGui->content_size.y);
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, m_Renderer->Get_FrameBuffer()->Get_FrameWidth(), m_Renderer->Get_FrameBuffer()->Get_FrameHeight());
		std::cout << "---------------------------------" << std::endl;
		m_MyGui->hit = false;
	}

	if (m_MyGui->Get_NewGameLayout().effect) 
	{
		m_City = new City(m_MyGui->Get_NewGameLayout().size);

		m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
		m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));

		m_MyGui->Get_NewGameLayout().effect = false;
		changed = true;
	}


	//------------------------------

	static double lastTime = glfwGetTime();

	double m_CurrentTime = glfwGetTime();
	m_FrameCounter++;

	if (m_CurrentTime - lastTime >= 1.0)
	{
		std::cout << m_FrameCounter << std::endl;

		m_FrameCounter = 0;
		lastTime += 1.0;
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
		transforms_CUBE.clear();
		transforms_CONE.clear();
		transforms_CYLINDER.clear();
		transforms_PYRAMID.clear();
		transforms_SPHERE.clear();

		transforms_EMPTY.clear();
		transforms_ROAD.clear();
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

		for (int i = 0; i < m_City->Get_GameTableSize(); i++)
		{
			for (int j = 0; j < m_City->Get_GameTableSize(); j++)
			{
				GameField* field = m_City->Get_GameField(i, j);
				glm::mat4 transform = glm::translate(glm::vec3(2 * j + 1, 0, 2 * i + 1));

				if (field->IsEmpty()) 
				{
					transforms_EMPTY.push_back(transform);
				}
				else if (field->IsRoad()) 
				{
					transforms_ROAD.push_back(transform);
				}
				else if (field->IsForest())
				{
					transforms_FOREST.push_back(transform);
				}
				else if (field->IsZone())
				{
					Zone* zone = dynamic_cast<Zone*>(field);
					if (zone->IsResidentalArea()) 
					{
						switch(zone->Get_Level())
						{
						case LEVEL_1: transforms_RESIDENCE1.push_back(transform); break;
						case LEVEL_2: transforms_RESIDENCE2.push_back(transform); break;
						case LEVEL_3: transforms_RESIDENCE3.push_back(transform); break;
						}
					}
					else if (zone->IsWorkingArea()) 
					{
						WorkingArea* area = dynamic_cast<WorkingArea*>(zone);
						if (area->IsIndustrialArea()) 
						{
							switch (area->Get_Level())
							{
							case LEVEL_1: transforms_INDUSTRY1.push_back(transform); break;
							case LEVEL_2: transforms_INDUSTRY2.push_back(transform); break;
							case LEVEL_3: transforms_INDUSTRY3.push_back(transform); break;
							}
						}
						else if (area->IsServiceArea())
						{
							switch (area->Get_Level())
							{
							case LEVEL_1: transforms_SERVICE1.push_back(transform); break;
							case LEVEL_2: transforms_SERVICE2.push_back(transform); break;
							case LEVEL_3: transforms_SERVICE3.push_back(transform); break;
							}
						}
					}
				}
				else if (field->IsBuilding()) 
				{
					Building* building = dynamic_cast<Building*>(field);
					if (building->IsPoliceStation()) 
					{
						transforms_FIRESTATION.push_back(transform);
					}
					else if (building->IsFireStation()) 
					{
						transforms_POLICESTATION.push_back(transform);
					}
					else if (building->IsStadium())
					{
						transforms_STADION.push_back(transform);
					}
					else if (building->IsSchool()) 
					{
						School* school = dynamic_cast<School*>(building);
						if (school->IsHighSchool()) 
						{
							transforms_SCHOOL1.push_back(transform);
						}
						else if (school->IsUniversity()) 
						{
							transforms_SCHOOL2.push_back(transform);
						}
					}
					else if (building->IsPowerStation()) 
					{
						transforms_POWERSTATION.push_back(transform);
					}
					else if (building->IsPowerWire())
					{
						transforms_POWERWIRE.push_back(transform);
					}
				}
			}
		}
		changed = false;
	}

	//case 19: transforms_CHARACTER.push_back(transform); break;

	m_Renderer->Render_PreRender();
	m_Renderer->RenderInstanced_Character(transforms_CHARACTER);
	m_Renderer->RenderInstanced_Empty(transforms_EMPTY);
	m_Renderer->RenderInstanced_Road(transforms_ROAD);
	m_Renderer->RenderInstanced_Forest(transforms_FOREST);
	m_Renderer->RenderInstanced_Residence1(transforms_RESIDENCE1);
	m_Renderer->RenderInstanced_Residence2(transforms_RESIDENCE2);
	m_Renderer->RenderInstanced_Residence3(transforms_RESIDENCE3);
	m_Renderer->RenderInstanced_Industry1(transforms_INDUSTRY1);
	m_Renderer->RenderInstanced_Industry2(transforms_INDUSTRY2);
	m_Renderer->RenderInstanced_Industry3(transforms_INDUSTRY3);
	m_Renderer->RenderInstanced_Service1(transforms_SERVICE1);
	m_Renderer->RenderInstanced_Service2(transforms_SERVICE2);
	m_Renderer->RenderInstanced_Service3(transforms_SERVICE3);
	m_Renderer->RenderInstanced_FireStation(transforms_FIRESTATION);
	m_Renderer->RenderInstanced_PoliceStation(transforms_POLICESTATION);
	m_Renderer->RenderInstanced_Stadion(transforms_STADION);
	m_Renderer->RenderInstanced_PowerStation(transforms_POWERSTATION);
	m_Renderer->RenderInstanced_PowerWire(transforms_POWERWIRE);
	m_Renderer->RenderInstanced_School1(transforms_SCHOOL1);
	m_Renderer->RenderInstanced_School2(transforms_SCHOOL2);
	m_Renderer->Render_Axis();
	m_Renderer->Render_Ray(RayOrigin, RayEnd);
	m_Renderer->Render_PostRender();
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

void Application::Keyboard_ButtonEvent(int key, int scancode, int action, int mods)
{
	if (ImGui::GetIO().WantCaptureKeyboard) return;

	m_Camera->Keyboard_ButtonEvent(key, scancode, action, mods);
};

void Application::Mouse_MoveEvent(double xpos, double ypos)
{
	if (ImGui::GetIO().WantCaptureMouse) return;

	m_Camera->Mouse_MoveEvent((float)xpos, (float)ypos);
};

void Application::Mouse_ClickEvent(int button, int action, int mods)
{
	if (ImGui::GetIO().WantCaptureMouse) return;

	m_Camera->Mouse_ClickEvent(button, action, mods);

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);
	}
};

void Application::Mouse_WeelEvent(double xoffset, double yoffset)
{
	if (ImGui::GetIO().WantCaptureMouse) return;

	m_Camera->Mouse_WheelEvent((float)xoffset, (float)yoffset);
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

		m_City->Set_GameTableValue(int(rayz), int(rayx), EMPTY);
		changed = true;
	}
}