#include "Application.h"

/**
 * Constructs an instance of the Application class.
 *
 * @param window A pointer to the GLFW window.
 * @param WINDOW_WIDTH The width of the window.
 * @param WINDOW_HEIGHT The height of the window.
 *
 * @returns An instance of the Application class.
 */
Application::Application(GLFWwindow* window, int WINDOW_WIDTH, int WINDOW_HEIGHT)
	:
	m_Window(window),
	m_WindowWidth(WINDOW_WIDTH),
	m_WindowHeight(WINDOW_HEIGHT)
{
	m_Camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_City = new City(50);

	Renderer::Init(m_Camera);
	Renderer::ResizeShapeBuffers(m_City->Get_GameTableSize() * m_City->Get_GameTableSize());

	m_MyGui = new MyGui(m_Camera);

	m_FrameCounter = new FrameCounter();
	m_Timer = new Timer(0.1f);
	m_Timer->Start();

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));

	MeteorGrp::Init();

	m_MyGui->Get_RenderWindowLayout().Lights_Effect = true;
	m_MyGui->Get_RenderWindowLayout().Lights_Reset = true;
	changed = true;

	SetUI_BuildCosts();
}

/**
 * Destructor for the Application class.
 * Deletes the dynamically allocated memory for the camera, GUI, and city objects.
 *
 * @returns None
 */
Application::~Application()
{
	delete m_Camera;
	delete m_MyGui;
	delete m_City;
}

/**
 * Updates the application based on the current UI mode.
 *
 * If the UI mode is LOBBY, the game is loaded and the camera is updated based on the current time. The viewport layout is updated, and various events are triggered, including animation updates, viewport events, game tick events, and lights changed events.
 *
 * If the UI mode is not LOBBY, the InitLobby flag is set to true, and if the game window is paused, various events are triggered, including viewport events, save game events, load game events, new game events, time tick changed events, tax changed events. If the game window is not paused, the InitLobby flag is set to false, and if the city's combined
 */
void Application::Update()
{
	if (m_MyGui->UI_MODE == LOBBY)
	{
		if (InitLobby)
		{
			Application::LoadGame(true);
			InitLobby = false;
		}

		m_Camera->Set_Eye(glm::vec3(50.f * cosf(static_cast<float>(glfwGetTime() * 2 * M_PI / 250)) + m_City->Get_GameTableSize(), 25.f, 50.f * sinf(static_cast<float>(glfwGetTime() * 2 * M_PI) / 250.f) + m_City->Get_GameTableSize()));
		m_MyGui->Get_ViewPortLayout().ViewPort_TextureID = Renderer::Get_FrameBuffer()->Get_TextureId();

		Application::UpdateAnimationAndMembers();
		Application::ViewPortEvent();
		Application::GameTickEvent();
		Application::LightsChangedEvent();
	}
	else 
	{
		InitLobby = true;
		if (m_MyGui->Get_GameWindowLayout().PauseTime)
		{
			if (!m_Timer->IsPaused())
			{
				m_Timer->Pause();
			}

			Application::ViewPortEvent();
			Application::SaveGameEvent();
			Application::LoadGameEvent();
			Application::NewGameEvent();
			Application::TimeTickChangedEvent();
			Application::TaxChangedEvent();
		}
		else
		{
			if (m_Timer->IsPaused())
			{
				m_Timer->Reset();
				m_Camera->ResetTimer();
				MeteorGrp::ResetTimer();
				CarGroup::ResetTimer();
				//Reset WaterCurves
				for (auto it = truck_map.begin(); it != truck_map.end(); it++)
				{
					it->second->ResetTimer();
				}
			}

			if (m_City->Get_CombinedHappiness() <= -80 || m_City->Get_Money() <= -50000000)
			{
				m_MyGui->Get_DetailsWindowLayout().End_Show = true;
				m_MyGui->Get_GameWindowLayout().PauseTime = true;
			}

			Application::UpdateAnimationAndMembers();
			Application::ViewPortEvent();
			Application::GameTickEvent();
			Application::SaveGameEvent();
			Application::LoadGameEvent();
			Application::NewGameEvent();
			Application::TimeTickChangedEvent();
			Application::MeteorStartEvent();
			Application::TaxChangedEvent();
			Application::FpsChangedEvent();
			Application::CameraChangedEvent();
			Application::LightsChangedEvent();
			Application::LogChagendEvent();
			Application::DetailsCheckEvent();
			Application::BuildEvent();
			Application::MeteorHitEvent();
			Application::UpgradeEvent();
		}
	}
}

/**
 * Renders the user interface based on the current UI mode.
 */
void Application::RenderUI()
{
	m_MyGui->Pre_Render();

	if (m_MyGui->UI_MODE == LOBBY)
	{
		m_MyGui->LOBBY_UI();
	}
	if (m_MyGui->UI_MODE == GAME)
	{
		m_MyGui->GAME_UI();
	}

	m_MyGui->Post_Render();
}

/**
 * Renders the current state of the game.
 */
void Application::Render()
{
	if (changed || Zone::CHANGED || City::CHANGED || GameTable::CHANGED)
	{
		std::unordered_set<GameField*> fields_2x2;
		for (int i = 0; i < m_City->Get_GameTableSize(); i++)
		{
			for (int j = 0; j < m_City->Get_GameTableSize(); j++)
			{
				int type = m_City->Get_GameField(i, j)->Get_Type();
				int amount = 1;
				int contain = 0;

				if (m_City->Get_GameField(i, j)->IsZone())
				{
					Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(i, j));			
					contain = zone->Get_Contain();
					if (type == RESIDENTIAL_LVL1) amount = contain;
					if (type == RESIDENTIAL_LVL2) amount = contain / 2 + contain % 2;
					if (type == RESIDENTIAL_LVL3) amount = contain / 8 + (contain % 8 == 0 ? 0 : 1);
					if (type == INDUSTRIAL_LVL1) amount = contain;
					if (type == INDUSTRIAL_LVL2) amount = contain;
					if (type == INDUSTRIAL_LVL3) amount = contain;
					if (type == SERVICE_LVL1) amount = contain;
					if (type == SERVICE_LVL2) amount = contain / 2 + contain % 2;
					if (type == SERVICE_LVL3) amount = contain / 4 + (contain % 4 == 0 ? 0 : 1);			
				}

				if (m_City->Get_GameField(i, j)->IsForest())
				{
					Forest* zone = dynamic_cast<Forest*>(m_City->Get_GameField(i, j));
					amount = zone->Get_Age() + 1;
				}

				if (type == UNIVERSITY || type == STADIUM || type == HIGHSCHOOL)
				{
					if (fields_2x2.find(m_City->Get_GameField(i, j)) != fields_2x2.end()) continue;
					fields_2x2.insert(m_City->Get_GameField(i, j));
				}

				Renderer::AddShapeTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_Direction(), amount);
				Renderer::AddGroundTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_Direction(), type == ROAD ? DetermineRoadTextureID(i, j) : m_City->Get_GameField(i, j)->OnFire() ? 37 : Renderer::DetermineGroundTextureID((RenderShapeType)type, contain));
			}
		}

		Renderer::Changed = true;
		Zone::CHANGED = false;
		City::CHANGED = false;
		GameTable::CHANGED = false;
		changed = false;
	}

	Renderer::PreRender();
	Renderer::SceneRender(INSTANCED);

	for (auto it = truck_map.begin(); it != truck_map.end(); it++)
	{
		Renderer::RenderWaterCurve(it->second->Get_Transforms());
	}

	if (m_MyGui->BuildHover)
	{
		ConvertMouseInputTo3D(m_MyGui->Get_EventLayout().Mouse_X, m_MyGui->Get_EventLayout().Mouse_Y, (int)m_MyGui->Get_EventLayout().Content_X, (int)m_MyGui->Get_EventLayout().Content_Y);

		bool l1 = HitX >= 0 && HitX < m_City->Get_GameTableSize();
		bool l2 = HitY >= 0 && HitY < m_City->Get_GameTableSize();

		if (l1 && l2)
		{
			FieldType type = (FieldType)m_MyGui->Get_BuildWindowLayout().Build_Id;
			FieldDirection dir = (FieldDirection)(m_MyGui->Get_EventLayout().Rotate % 4);

			Renderer::Buildable = m_City->IsBuildable(type, dir, HitX, HitY);
			if (m_MyGui->Get_BuildWindowLayout().Build_Id == RENDER_WINDTURBINE)
			{
				Renderer::RenderNormal(RENDER_WINDTURBINE_PROPELLER, HitX, HitY, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildWindowLayout().Build_Id, HitX, HitY, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal(RENDER_WINDTURBINE_PROPELLER, HitX + 1, HitY, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildWindowLayout().Build_Id, HitX + 1, HitY, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal(RENDER_WINDTURBINE_PROPELLER, HitX, HitY + 1, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildWindowLayout().Build_Id, HitX, HitY + 1, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal(RENDER_WINDTURBINE_PROPELLER, HitX + 1, HitY + 1, (m_MyGui->Get_EventLayout().Rotate % 4));
				Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildWindowLayout().Build_Id, HitX + 1, HitY + 1, (m_MyGui->Get_EventLayout().Rotate % 4));
			}
			else 
			{
				Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildWindowLayout().Build_Id, HitX, HitY, (m_MyGui->Get_EventLayout().Rotate % 4));
			}
		}
	}

	Renderer::PostRender();
}


//---------------------------------------------------------|Events|---------------------------------------------------------//
//---------------------------------------------------------|Events|---------------------------------------------------------//
//---------------------------------------------------------|Events|---------------------------------------------------------//

/**
 * Event handler for when the application window is resized.
 *
 * @param width The new width of the window.
 * @param height The new height of the window.
 *
 * @returns None
 */
void Application::Window_ResizedEvent(int width, int height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
};

/**
 * Event handler for when the application's frame buffer is resized.
 * Updates the camera's projection matrix to match the new dimensions.
 *
 * @param width The new width of the frame buffer.
 * @param height The new height of the frame buffer.
 *
 * @returns None
 */
void Application::FrameBuffer_ResizedEvent(int width, int height)
{
	m_Camera->Set_ProjMatrix(width, height);
};

/**
 * Converts mouse input coordinates to 3D coordinates in the world space.
 *
 * @param xpos The x-coordinate of the mouse input.
 * @param ypos The y-coordinate of the mouse input.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 * @returns None
 */
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

		HitX = (int)rayz;
		HitY = (int)rayx;
	}
}

/**
 * Determines the texture ID of a road tile based on its surrounding tiles.
 *
 * @param x The x-coordinate of the road tile.
 * @param y The y-coordinate of the road tile.
 *
 * @returns The texture ID of the road tile.
 */
int Application::DetermineRoadTextureID(int x, int y)
{
	bool upper_field = false;
	bool lower_field = false;
	bool left_field = false;
	bool right_field = false;

	if (y + 1 < m_City->Get_GameTableSize())
		upper_field = m_City->Get_GameField(x, y + 1)->IsRoad();
	if (y - 1 >= 0)
		lower_field = m_City->Get_GameField(x, y - 1)->IsRoad();
	if (x + 1 < m_City->Get_GameTableSize())
		right_field = m_City->Get_GameField(x + 1, y)->IsRoad();
	if (x - 1 >= 0)
		left_field = m_City->Get_GameField(x - 1, y)->IsRoad();

	if (upper_field && lower_field && right_field && left_field)
	{
		return 5; //Keresztez�d�s
	}
	else if ((upper_field && !lower_field && !right_field && !left_field) || (!upper_field && lower_field && !right_field && !left_field) || (upper_field && lower_field && !right_field && !left_field))
	{
		return 6; //�tmen� fel-le
	}
	else if ((!upper_field && !lower_field && right_field && !left_field) || (!upper_field && !lower_field && !right_field && left_field) || (!upper_field && !lower_field && right_field && left_field))
	{
		return 106; //�tmen� jobbra-balra
	}
	else if ((upper_field && !lower_field && right_field && left_field))
	{
		return 4; //H�rom �g� balra-fel-jobbra
	}
	else if ((!upper_field && lower_field && right_field && left_field))
	{
		return 204; //H�rom �g� balra-le-jobbra
	}
	else if ((upper_field && lower_field && right_field && !left_field))
	{
		return 304;//H�rom �g� jobbra-fel-le
	}
	else if ((upper_field && lower_field && !right_field && left_field))
	{
		return 104;//H�rom �g� balra-fel-le
	}
	else if ((!upper_field && lower_field && right_field && !left_field))
	{
		return 103;//kanyar lentr�l-jobbra
	}
	else if ((!upper_field && lower_field && !right_field && left_field))
	{
		return 3;//kanyar lentr�l-balra
	}
	else if ((upper_field && !lower_field && !right_field && left_field))
	{
		return 303;//kanyar balr�l-felfele
	}
	else if ((upper_field && !lower_field && right_field && !left_field))
	{
		return 203;//kanyar jobbr�l-felfele
	}
	else
	{
		return 6;
	}
}


/**
 * Simulates the movement and actions of fire trucks in the city.
 *
 * @returns None
 */
void Application::FireTruckSimulation()
{
	std::vector<Car*> to_delete_CARGROUP;
	std::vector<Car*> to_delete_MAP;

	for (auto truck : CarGroup::m_FireTrucks)
	{
		float dir = 0.02f * cosf(truck->Get_Rotation());

		float rotation = 0;
		float start_x = truck->Get_CurrentPosition(rotation).x + dir;
		float start_y = truck->Get_CurrentPosition(rotation).z + dir;

		int table_x = static_cast<int>(start_y / 2.f);
		int table_y = static_cast<int>(start_x / 2.f);

		FieldType type = m_City->Get_GameField(table_x, table_y)->Get_Type();

		if (type == EMPTY || type == CRATER)
		{
			if (station_map.find(truck) != station_map.end())
			{			
				to_delete_MAP.push_back(truck);
			}

			to_delete_CARGROUP.push_back(truck);
		}
	}

	for (auto car : to_delete_MAP)
	{
		station_map.erase(car);
		truck_map.erase(car);
	}

	for (auto car : to_delete_CARGROUP)
	{
		CarGroup::m_FireTrucks.erase(car);
	}


	std::vector<Car*> no_start;
	for (auto truck : CarGroup::m_FireTrucks)
	{
		if (truck->ShouldBeDeleted() && truck_map.find(truck) == truck_map.end())
		{
			float dir = 0.02f * cosf(truck->Get_Rotation());

			float rotation = 0;
			float start_x = truck->Get_CurrentPosition(rotation).x + dir;
			float start_y = truck->Get_CurrentPosition(rotation).z + dir;

			int table_x = static_cast<int>(start_y / 2.f);
			int table_y = static_cast<int>(start_x / 2.f);

			float end_x = -1;
			float end_y = -1;

			if (m_City->Validate(table_x + 1, table_y) && m_City->Get_GameField(table_x + 1, table_y)->OnFire())
			{
				end_x = table_y * 2.f + 1;
				end_y = (table_x + 1) * 2.f + 1;
			}
			else if (m_City->Validate(table_x - 1, table_y) && m_City->Get_GameField(table_x - 1, table_y)->OnFire())
			{
				end_x = table_y * 2.f + 1;
				end_y = (table_x - 1) * 2.f + 1;
			}
			else if (m_City->Validate(table_x, table_y + 1) && m_City->Get_GameField(table_x, table_y + 1)->OnFire())
			{
				end_x = (table_y + 1) * 2.f + 1;
				end_y = table_x * 2.f + 1;
			}
			else if (m_City->Validate(table_x, table_y - 1) && m_City->Get_GameField(table_x, table_y - 1)->OnFire())
			{
				end_x = (table_y - 1) * 2.f + 1;
				end_y = table_x * 2.f + 1;
			}

			if (end_x != -1)
			{
				truck_map.insert(std::pair<Car*, WaterGroup*>(truck, new WaterGroup(start_x, start_y, end_x, end_y)));
			}
			else 
			{
				station_map.erase(truck);
				no_start.push_back(truck);
			}
		}
	}

	for (auto car : no_start)
	{
		CarGroup::m_FireTrucks.erase(car);
	}

	std::vector<Car*> to_Delete;

	for (auto it = truck_map.begin(); it != truck_map.end(); it++)
	{
		it->second->Update();

		int x = (int)it->second->endY / 2;
		int y = (int)it->second->endX / 2;

		if (!m_City->Get_GameField(x, y)->OnFire())
		{
			float start_x = it->second->startX;
			float start_y = it->second->startY;

			it->second->Clear();
			delete it->second;
			it->second = nullptr;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (m_City->Validate(x + i, y + j) && !(i == 0 && j == 0) && m_City->Get_GameField(x + i, y + j)->OnFire())
					{
						it->second = new WaterGroup(start_x, start_y, 2.f * (y + j) + 1, 2.f * (x + i) + 1);
					}
				}
			}
			
			if (it->second == nullptr)
			{
				std::unordered_set<int> onFireFields = m_City->Get_GameTable()->PathFinder_Fire({ (int)start_y / 2, (int)start_x / 2 });

				if (onFireFields.size() > 0)
				{
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distr(0, (int)onFireFields.size() - 1);

					auto beginIT = onFireFields.begin();
					std::advance(beginIT, distr(gen));

					int randomField = *beginIT;
					
					it->second = new WaterGroup(start_x, start_y, 2.f * (randomField % m_City->Get_GameTableSize()) + 1, 2.f * (randomField / m_City->Get_GameTableSize()) + 1);
				}
			}
			
			if (it->second == nullptr)
			{
				to_Delete.push_back(it->first);
			}
		}
	}

	for (auto truck : to_Delete)
	{
		truck_map.erase(truck);
		station_map.erase(truck);
		CarGroup::m_FireTrucks.erase(truck);
	}
}


/**
 * Checks the position of each car in the CarGroup and removes any cars that are on an invalid game field.
 * Also removes any intersections that are associated with the removed cars.
 *
 * @returns None
 */
void Application::CheckCarPos()
{
	std::vector<Car*> delete_cars;
	std::vector<CarAndCoord*> to_delete;

	for (auto car : CarGroup::m_Cars)
	{
		float rotation = 0;
		float start_x = car->Get_CurrentPosition(rotation).x;
		float start_y = car->Get_CurrentPosition(rotation).z;

		int table_x = static_cast<int>(start_y / 2.f);
		int table_y = static_cast<int>(start_x / 2.f);

		FieldType type = m_City->Get_GameField(table_x, table_y)->Get_Type();

		if (type == EMPTY || type == CRATER)
		{
			delete_cars.push_back(car);

			for (auto it = CarGroup::m_InUseIntersections.begin(); it != CarGroup::m_InUseIntersections.end(); it++)
			{
				if ((*it)->Get_Car() == car)
				{
					to_delete.push_back(*it);
				}
			}

			for (auto car : to_delete)
			{
				CarGroup::m_InUseIntersections.erase(car);
			}
		}
	}

	for (auto car : delete_cars)
	{
		CarGroup::m_Cars.erase(car);
	}


}

/**
 * Sets the UI build costs for different types of buildings.
 */
void Application::SetUI_BuildCosts()
{
	m_MyGui->Get_BuildWindowLayout().RoadCost = GameField::CalculateBuildCost(ROAD);
	m_MyGui->Get_BuildWindowLayout().ForestCost = GameField::CalculateBuildCost(FOREST);
	m_MyGui->Get_BuildWindowLayout().ResidenceCost = GameField::CalculateBuildCost(RESIDENTIAL_LVL1);
	m_MyGui->Get_BuildWindowLayout().IndustryCost = GameField::CalculateBuildCost(INDUSTRIAL_LVL1);
	m_MyGui->Get_BuildWindowLayout().ServiceCost = GameField::CalculateBuildCost(SERVICE_LVL1);
	m_MyGui->Get_BuildWindowLayout().FireStationCost = GameField::CalculateBuildCost(FIRESTATION);
	m_MyGui->Get_BuildWindowLayout().PoliceStationCost = GameField::CalculateBuildCost(POLICESTATION);
	m_MyGui->Get_BuildWindowLayout().StadionCost = GameField::CalculateBuildCost(STADIUM);
	m_MyGui->Get_BuildWindowLayout().HighSchoolCost = GameField::CalculateBuildCost(HIGHSCHOOL);
	m_MyGui->Get_BuildWindowLayout().UniversityCost = GameField::CalculateBuildCost(UNIVERSITY);
	m_MyGui->Get_BuildWindowLayout().PowerStationCost = GameField::CalculateBuildCost(POWERSTATION);
}

/**
 * Handles the new game event triggered by the user.
 * If the new game effect is enabled, it disables it and starts a new game with the specified city size.
 */
void Application::NewGameEvent()
{
	if (m_MyGui->Get_MenuBarLayout().NewGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().NewGame_Effect = false;
		Application::NewGame(m_MyGui->Get_MenuBarLayout().City_Size, -1, -1);
	}
}

/**
 * Saves the current game state if the Save Game effect is enabled in the GUI.
 */
void Application::SaveGameEvent()
{
	if (m_MyGui->Get_MenuBarLayout().SaveGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().SaveGame_Effect = false;
		Application::SaveGame();
	}
}

/**
 * Loads the game when the Load Game event is triggered by the GUI.
 */
void Application::LoadGameEvent()
{
	if (m_MyGui->Get_MenuBarLayout().LoadGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().LoadGame_Effect = false;
		Application::LoadGame();
	}
}

/**
 * Event handler for when the time tick changes in the application.
 * If the time effect is enabled, sets the tick time of the timer to the new value.
 */
void Application::TimeTickChangedEvent()
{
	if (m_MyGui->Get_GameWindowLayout().Time_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Time_Effect = false;
		m_Timer->SetTickTime(m_MyGui->Get_GameWindowLayout().Time_Tick);
	}
}

/**
 * Event handler for when the FPS changes.
 * Updates the FPS and frame time in the GUI.
 */
void Application::FpsChangedEvent()
{
	if (m_FrameCounter->Tick())
	{
		m_MyGui->Get_RenderWindowLayout().Frame_Fps = m_FrameCounter->Get_FPS();
		m_MyGui->Get_RenderWindowLayout().Frame_Time = m_FrameCounter->Get_DeltaTime();
		m_FrameCounter->Reset();
	}
}

/**
 * Event handler for when the camera is changed in the application.
 * If the camera effect is enabled, it disables it and sets the camera mode and speed based on the user's input.
 */
void Application::CameraChangedEvent()
{
	if (m_MyGui->Get_RenderWindowLayout().Camera_Effect)
	{
		m_MyGui->Get_RenderWindowLayout().Camera_Effect = false;
		m_Camera->Set_Mode(m_MyGui->Get_RenderWindowLayout().Camera_Mode, 0, 0);
		m_Camera->Get_Speed() = m_MyGui->Get_RenderWindowLayout().Camera_Speed;
	}
}

/**
 * Event handler for when the lights are changed in the application.
 * Updates the light properties based on the user's input.
 */
void Application::LightsChangedEvent()
{
	if (m_MyGui->Get_RenderWindowLayout().Lights_Effect)
	{
		LightProperties r_LightProperties;
		r_LightProperties.lightDir = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(1, -1, 1) : m_MyGui->Get_RenderWindowLayout().Lights_Direction;
		r_LightProperties.specularPow = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? 64 : m_MyGui->Get_RenderWindowLayout().Lights_SpecularPow;
		r_LightProperties.La = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(0.5, 0.5, 0.5) : m_MyGui->Get_RenderWindowLayout().La;
		r_LightProperties.Ld = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(1, 1, 0.85) : m_MyGui->Get_RenderWindowLayout().Ld;
		r_LightProperties.Ls = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(1, 1, 1) : m_MyGui->Get_RenderWindowLayout().Ls;
		r_LightProperties.Ka = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(0.8, 0.8, 0.8) : m_MyGui->Get_RenderWindowLayout().Ka;
		r_LightProperties.Kd = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(1, 1, 1) : m_MyGui->Get_RenderWindowLayout().Kd;
		r_LightProperties.Ks = m_MyGui->Get_RenderWindowLayout().Lights_Reset ? glm::vec3(0.7, 0.6, 0.6) : m_MyGui->Get_RenderWindowLayout().Ks;
		Renderer::Set_LightProperties(r_LightProperties);

		m_MyGui->Get_RenderWindowLayout().Lights_Effect = false;
		m_MyGui->Get_RenderWindowLayout().Lights_Reset = false;
	}
}

/**
 * Event handler for when the tax rate is changed in the GUI.
 * Updates the tax rates in the city object.
 */
void Application::TaxChangedEvent()
{
	if (m_MyGui->Get_GameWindowLayout().Tax_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Tax_Effect = false;
		std::vector<std::pair<FieldType, float*>> taxRates = Application::Get_TaxRates();

		for (auto& it : taxRates)
		{
			m_City->Set_TaxRate(it.first, *it.second);
		}
	}
}

/**
 * Logs the changes in the city and citizen data to the GUI log window.
 */
void Application::LogChagendEvent()
{
	m_MyGui->Get_LogWindowLayout().build_log = City::BUILD_LOG.str();
	m_MyGui->Get_LogWindowLayout().citizen_log = Citizen::LOG.str();
	m_MyGui->Get_LogWindowLayout().money_log = City::MONEY_LOG.str();
}

/**
 * Upgrades a field in the city when the upgrade event is triggered.
 */
void Application::UpgradeEvent()
{
	if (m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect)
	{
		m_City->UpgradeField(m_MyGui->Get_DetailsWindowLayout().Field_X, m_MyGui->Get_DetailsWindowLayout().Field_Y);
		m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect = false;
		changed = true;
	}
}


/**
 * Triggers a meteor start event that adds meteors to the game window layout.
 */
void Application::MeteorStartEvent()
{
	if (m_MyGui->Get_GameWindowLayout().Catastrophe_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Catastrophe_Effect = false;

		for (int i = 0; i < m_MyGui->Get_GameWindowLayout().Catastrophe_Count; i++)
		{
			MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
		}
	}
}

/**
 * Handles the event when a meteor hits the city in the game.
 */
void Application::MeteorHitEvent()
{
	//METEOR HITS GROUND
	if (MeteorGrp::Effect())
	{
		auto fields = MeteorGrp::Change();

		for (auto field : fields)
		{
			m_City->Set_GameTableValue(field.first, field.second, CRATER, (FieldDirection)LEFT);
			changed = true;
		}

		MeteorGrp::Delete();
	}
}

/**
 * Checks the event details of the current game field and updates the details window layout accordingly.
 */
void Application::DetailsCheckEvent()
{
	if (m_City->Get_GameField(m_MyGui->Get_DetailsWindowLayout().Details_X, m_MyGui->Get_DetailsWindowLayout().Details_Y)->IsZone())
	{
		Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(m_MyGui->Get_DetailsWindowLayout().Details_X, m_MyGui->Get_DetailsWindowLayout().Details_Y));
		m_MyGui->Get_DetailsWindowLayout().Details = Zone::ToString(zone);
	}
	else if (m_City->Get_GameField(m_MyGui->Get_DetailsWindowLayout().Details_X, m_MyGui->Get_DetailsWindowLayout().Details_Y)->IsBuilding())
	{
		Building* building = dynamic_cast<Building*>(m_City->Get_GameField(m_MyGui->Get_DetailsWindowLayout().Details_X, m_MyGui->Get_DetailsWindowLayout().Details_Y));
		m_MyGui->Get_DetailsWindowLayout().Details = Building::ToString(building);
	}
	else
	{
		GameField* field = m_City->Get_GameField(m_MyGui->Get_DetailsWindowLayout().Details_X, m_MyGui->Get_DetailsWindowLayout().Details_Y);
		m_MyGui->Get_DetailsWindowLayout().Details = GameField::ToString(field);
	}
}

/**
 * Handles the viewport event and resizes the frame buffer if necessary.
 */
void Application::ViewPortEvent()
{
	if (m_MyGui->Get_ViewPortLayout().ViewPort_Effect)
	{
		int width = m_MyGui->Get_ViewPortLayout().ViewPort_Width;
		int height = m_MyGui->Get_ViewPortLayout().ViewPort_Height;
		Renderer::Get_FrameBuffer()->Resize(width, height);
	}
}

/**
 * Updates the animation and members of the application.
 */
void Application::UpdateAnimationAndMembers()
{
	MeteorGrp::Update();
	CarGroup::Update();
	CheckCarPos();
	FireTruckSimulation();
	m_Timer->Update();
	m_FrameCounter->Update();
	m_Camera->Update();

	m_MyGui->Get_ViewPortLayout().ViewPort_TextureID = Renderer::Get_FrameBuffer()->Get_TextureId();
	m_MyGui->Get_RenderWindowLayout().Camera_Position = m_Camera->Get_CameraEye();
	m_MyGui->Get_DetailsWindowLayout().Network_details = RoadNetwork::NetworksToString();
	m_MyGui->Get_BuildWindowLayout().TextureID = Renderer::Get_Texture()->Get_TextureID();
}

/**
 * Builds an event based on user input from the GUI.
 */
void Application::BuildEvent()
{
	//BUILD - OR MOUSE EVENT
	if (m_MyGui->Get_EventLayout().Hit)
	{
		m_MyGui->Get_EventLayout().Hit = false;
		ConvertMouseInputTo3D(m_MyGui->Get_EventLayout().Mouse_X, m_MyGui->Get_EventLayout().Mouse_Y, Renderer::Get_FrameBuffer()->Get_FrameWidth(), Renderer::Get_FrameBuffer()->Get_FrameHeight());
		
		Application::BuildEvent_CheckField();
		Application::BuildEvent_Upgrade();
		Application::BuildEvent_SetFire();
		Application::BuildEvent_SendTruck();
		Application::BuildEvent_BuildField();
	}
}

/**
 * Builds an event to check the field in the application.
 *
 * If the build ID is -1, the details window layout is updated with the current hit coordinates.
 */
void Application::BuildEvent_CheckField()
{
	if (m_MyGui->Get_BuildWindowLayout().Build_Id == -1)
	{
		m_MyGui->Get_DetailsWindowLayout().Details_X = HitX;
		m_MyGui->Get_DetailsWindowLayout().Details_Y = HitY;
	}
}

/**
 * Builds the event for upgrading a zone in the city.
 */
void Application::BuildEvent_Upgrade()
{
	if (m_MyGui->Get_BuildWindowLayout().Build_Id == -2)
	{
		if (m_City->Get_GameField(HitX, HitY)->IsZone())
		{
			Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(HitX, HitY));

			m_MyGui->Get_DetailsWindowLayout().Field_Type = zone->Get_Type();
			m_MyGui->Get_DetailsWindowLayout().Field_X = HitX;
			m_MyGui->Get_DetailsWindowLayout().Field_Y = HitY;
			m_MyGui->Get_DetailsWindowLayout().Upgrade_Cost = GameField::CalculateBuildCost((FieldType)((int)zone->Get_Type() + 1));

			m_MyGui->Get_DetailsWindowLayout().Upgrade_Show = true;
			m_MyGui->Get_DetailsWindowLayout().level = zone->Get_Level();
		}
	}
}

/**
 * Sets a game field on fire if it is a zone or building and not a fire station.
 */
void Application::BuildEvent_SetFire()
{
	if (m_MyGui->Get_BuildWindowLayout().Build_Id == -3)
	{
		GameField* field = m_City->Get_GameField(HitX, HitY);
		if ((field->IsZone() || field->IsBuilding()) && field->Get_Type() != FIRESTATION)
		{
			field->OnFire() = true;
			changed = true;
		}
	}
}

/**
 * Builds an event to send a truck to a fire station.
 */
void Application::BuildEvent_SendTruck()
{
	if (m_MyGui->Get_BuildWindowLayout().Build_Id == -4)
	{
		if (m_City->Get_GameField(HitX, HitY)->Get_Type() == FIRESTATION)
		{
			std::vector<Point> fireTrucks = m_City->Get_FireTruckPath(HitX, HitY);
			std::vector<CarCoord> coordinates;

			for (int i = 0; i < fireTrucks.size(); ++i)
			{
				coordinates.push_back({ glm::vec3(fireTrucks[i].y * 2 + 1, 0, fireTrucks[i].x * 2 + 1) });
			}

			bool l = false;
			for (auto it = station_map.begin(); it != station_map.end() && !l; it++)
			{
				l = l || it->second == m_City->Get_GameField(HitX, HitY);
			}

			if (coordinates.size() > 1 && !l)
			{
				Car* new_car = CarGroup::AddFireTruck(coordinates);
				station_map.insert(std::pair<Car*, GameField*>(new_car, m_City->Get_GameField(HitX, HitY)));
			}

		}
	}
}

void Application::BuildEvent_BuildField()
{
	if (m_MyGui->Get_BuildWindowLayout().Build_Id >= 0)
	{
		FieldType type = (FieldType)m_MyGui->Get_BuildWindowLayout().Build_Id;
		FieldDirection dir = (FieldDirection)(m_MyGui->Get_EventLayout().Rotate % 4);

		if (m_City->IsBuildable(type, dir, HitX, HitY))
		{
			m_City->Set_GameTableValue(HitX, HitY, type, dir);
			changed = true;
		}
	}
}

/**
 * Handles the game tick event by simulating the city, updating the game UI members, and randomly generating meteors and cars.
 */
void Application::GameTickEvent()
{
	if (m_Timer->Tick())
	{
		int size = m_City->Get_CitizenSize();
		m_City->Simulate();

		Application::GameTickEvent_SetGameUiMembers();
		Application::GameTickEvent_RandomMeteors();
		Application::GameTickEvent_RandomCars();
		Application::GameTickEvent_Fire();

		changed = changed || m_City->Get_CitizenSize() != size;
	}
}

/**
 * Updates the game UI members with the current game state.
 */
void Application::GameTickEvent_SetGameUiMembers()
{
	m_MyGui->Get_GameWindowLayout().City_Money = m_City->Get_Money();
	m_MyGui->Get_GameWindowLayout().City_Satisfaction = static_cast<int>(m_City->Get_CombinedHappiness());
	m_MyGui->Get_GameWindowLayout().Time_Game = m_City->Get_TimeStr();
	m_MyGui->Get_GameWindowLayout().Time_Real += m_Timer->Get_TickTime();
}

/**
 * Generates random meteors in the game at a fixed interval.
 */
void Application::GameTickEvent_RandomMeteors()
{
	//Meteor shooting
	if (rand() % 500 == 23)
	{
		int number = rand() % 5;
		if (rand() % 43949268 == 538635) number = 2500;

		for (int i = 0; i < number; i++)
		{
			MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
		}
	}
}

/**
 * Generates random cars and adds them to the city.
 */
void Application::GameTickEvent_RandomCars()
{
	CarGroup::Set_CarLimit(m_City->Get_NumberOfResidences());

	std::vector<std::vector<Point>> cars = m_City->Get_CarPaths();
	for (int i = 0; i < cars.size(); ++i)
	{
		if (cars[i].size() > 1)
		{
			std::vector<CarCoord> coordinates;
			for (int j = 0; j < cars[i].size(); ++j)
			{
				coordinates.push_back({ glm::vec3(cars[i][j].y * 2 + 1, 0, cars[i][j].x * 2 + 1), cars[i][j].isInterSection });
			}
			CarGroup::Add(coordinates);
		}
	}
}

/**
 * Fires the GameTick event and updates the fire counter for each truck on the game field.
 */
void Application::GameTickEvent_Fire()
{
	for (auto it = truck_map.begin(); it != truck_map.end(); it++)
	{
		m_City->Get_GameField(static_cast<int>(it->second->endY / 2), static_cast<int>(it->second->endX / 2))->FireCounter += 2;

		if (m_City->Get_GameField(static_cast<int>(it->second->endY / 2), static_cast<int>(it->second->endX / 2))->FireCounter >= 500)
		{
			m_City->Get_GameField(static_cast<int>(it->second->endY / 2), static_cast<int>(it->second->endX / 2))->FireCounter = 500;
			m_City->Get_GameField(static_cast<int>(it->second->endY / 2), static_cast<int>(it->second->endX / 2))->OnFire() = false;
			changed = true;
		}
	}
}

/**
 * Starts a new game with the specified parameters.
 *
 * @param size The size of the game board.
 * @param money The starting amount of money. If not specified, defaults to -1.
 * @param time The starting time. If not specified, defaults to -1.
 */
void Application::NewGame(int size, int money = -1, int time = -1)
{
	m_MyGui->Get_DetailsWindowLayout().Details_X = 0;
	m_MyGui->Get_DetailsWindowLayout().Details_Y = 0;
	m_MyGui->Get_GameWindowLayout().PauseTime = false;
	m_MyGui->Get_GameWindowLayout().Time_Real = 0;
	m_MyGui->Get_GameWindowLayout().Time_Tick = m_MyGui->Get_MenuBarLayout().City_Time;
	m_Timer->Reset();
	m_Timer->SetTickTime(m_MyGui->Get_MenuBarLayout().City_Time);
	changed = true;

	CarGroup::ClearFireTrucks();
	MeteorGrp::Clear();
	CarGroup::Clear();
	RoadNetwork::ResetNetworks();
	City::BUILD_LOG.clear();
	City::BUILD_LOG.str("");
	City::MONEY_LOG.clear();
	City::MONEY_LOG.str("");
	Citizen::LOG.clear();
	Citizen::LOG.str("");
	Renderer::ResizeShapeBuffers(size * size);

	delete m_City;
	if (money == -1 || time == -1) m_City = new City(size);
	else m_City = new City(size, money, time);

	auto taxRates = Application::Get_TaxRates();
	for (auto& it : taxRates)
	{
		*it.second = 40;
	}
	m_MyGui->Get_GameWindowLayout().Tax_Effect = true;

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));
}

/**
 * Loads a saved game from a file.
 *
 * @param b A boolean value indicating whether to load the game from a default file or a user-specified file.
 */
void Application::LoadGame(bool b)
{
	std::ifstream saveFile;
	if (b == false) {
		saveFile.open(m_MyGui->Get_MenuBarLayout().LoadFile_Path);
	}
	else {
		saveFile.open("Application/lobbyfinal.txt");
	}
	

	if (!saveFile.is_open())
	{
		std::cout << "Could not open [" << m_MyGui->Get_MenuBarLayout().LoadFile_Path << "]" << std::endl;
		return;
	}

	int size, money, time;
	saveFile >> size >> money >> time;
	Application::NewGame(size, money, time);

	auto taxRates = Application::Get_TaxRates();
	for (auto& it : taxRates)
	{
		int type;
		float taxRate;
		saveFile >> type >> taxRate;
		m_City->Set_TaxRate(static_cast<FieldType>(type), taxRate);
		*it.second = taxRate;
	}

	//mez�k
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int type_i, dir_i;
			saveFile >> type_i >> dir_i;
			FieldType type = static_cast<FieldType>(type_i);
			FieldDirection dir = static_cast<FieldDirection>(dir_i);
			if (type == FOREST)
			{
				int tmp;
				saveFile >> tmp;
				m_City->Set_GameTableValue(i, j, type, dir, true);
				GameField* f = m_City->Get_GameField(i, j);
				dynamic_cast<Forest*>(f)->Set_Age(tmp);
			}
			else if (type != EMPTY)
			{
				m_City->Set_GameTableValue(i, j, type, dir, true);
			}
		}
	}

	//polg�rok
	int citizenSize, x, y;
	saveFile >> citizenSize;
	for (int i = 0; i < citizenSize; i++)
	{
		Citizen* citizen = new Citizen();
		saveFile >> x >> y;
		citizen->JoinZone(dynamic_cast<Zone*>(m_City->Get_GameField(x, y)));//lak�hely
		saveFile >> x >> y;
		if (x != -1 && y != -1)
		{
			citizen->JoinZone(dynamic_cast<Zone*>(m_City->Get_GameField(x, y)));//munkahely
		}
		saveFile >> x >> y;
		citizen->Set_Age(x);
		citizen->Set_Education(static_cast<Education>(y));
		saveFile >> x >> y;
		citizen->Set_MonthsBeforePension(x);
		citizen->Set_Pension((float)y);

		m_City->Get_Citizens().insert(citizen);
	}
	m_City->Set_InitialCitizens(m_City->Get_CitizenSize());
}

/**
 * Saves the current state of the game to a file.
 */
void Application::SaveGame()
{
	std::ofstream saveFile(m_MyGui->Get_MenuBarLayout().SaveFile_Path + ".txt");

	if (!saveFile.is_open())
	{
		std::cout << "Could not open [" << m_MyGui->Get_MenuBarLayout().SaveFile_Path + ".txt" << "]" << std::endl;
		return;
	}

	//V�ros adatai
	int size = m_City->Get_GameTableSize();
	saveFile << size << std::endl;
	saveFile << m_City->Get_Money() << std::endl;
	saveFile << m_City->Get_Time() << std::endl;

	auto taxRates = Application::Get_TaxRates();
	for (auto& it : taxRates)
	{
		saveFile << it.first << " " << *it.second << " ";
	}
	saveFile << std::endl;

	//Mez�k
	std::unordered_set<GameField*> bigBuildings;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GameField* field = m_City->Get_GameField(i, j);
			FieldType type = field->Get_Type();
			if (type == UNIVERSITY || type == HIGHSCHOOL || type == POWERSTATION || type == STADIUM)
			{
				if (bigBuildings.find(field) == bigBuildings.end())
				{
					bigBuildings.emplace(field);
					if (type == HIGHSCHOOL)
					{
						saveFile << type << " " << field->Get_Direction() << " ";
						continue;
					}
				}
				else
				{
					saveFile << EMPTY << " " << 0 << " ";
					continue;
				}
			}
			else if (type == FOREST)
			{
				saveFile << type << " " << field->Get_Direction() << " " << dynamic_cast<Forest*>(field)->Get_Age() << " ";
				continue;
			}
			saveFile << type << " " << field->Get_Direction() << " ";
		}
		saveFile << std::endl;
	}

	//Polg�rok
	saveFile << m_City->Get_CitizenSize() << std::endl;
	for (auto& citizen : m_City->Get_Citizens())
	{
		saveFile << citizen->Get_Residence()->Get_X() << " " << citizen->Get_Residence()->Get_Y() << " ";
		if (citizen->Get_Workplace() == nullptr)
		{
			saveFile << -1 << " " << -1 << " ";
		}
		else
		{
			saveFile << citizen->Get_Workplace()->Get_X() << " " << citizen->Get_Workplace()->Get_Y() << " ";
		}
		saveFile << citizen->Get_Age() << " " << citizen->Get_Education() << " ";
		saveFile << citizen->Get_MonthsBeforePension() << " " << citizen->Get_Pension() << std::endl;
	}
}

/**
 * Returns a vector of pairs containing the tax rates for different fields.
 *
 * @returns A vector of pairs containing the field type and its corresponding tax rate.
 */
std::vector<std::pair<FieldType, float*>> Application::Get_TaxRates()
{
	std::vector<std::pair<FieldType, float*>> taxRates = {
	{RESIDENTIAL_LVL1, &m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl1},
	{RESIDENTIAL_LVL2, &m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl2},
	{RESIDENTIAL_LVL3, &m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl3},
	{SERVICE_LVL1, &m_MyGui->Get_GameWindowLayout().ServiceTaxLvl1},
	{SERVICE_LVL2, &m_MyGui->Get_GameWindowLayout().ServiceTaxLvl2},
	{SERVICE_LVL3, &m_MyGui->Get_GameWindowLayout().ServiceTaxLvl3},
	{INDUSTRIAL_LVL1, &m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl1},
	{INDUSTRIAL_LVL2, &m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl2},
	{INDUSTRIAL_LVL3, &m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl3}
	};

	return taxRates;
}