#include "Application.h"

Application::Application(GLFWwindow* window, int WINDOW_WIDTH, int WINDOW_HEIGHT)
	:
	m_Window(window),
	m_WindowWidth(WINDOW_WIDTH),
	m_WindowHeight(WINDOW_HEIGHT)
{

	m_Camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_City = new City(50, 10000);

	Renderer::Init(m_Camera);
	Renderer::ResizeShapeBuffers(m_City->Get_GameTableSize() * m_City->Get_GameTableSize());

	m_MyGui = new MyGui(m_Camera);

	m_FrameCounter = new FrameCounter();
	m_Timer = new Timer(0.1);
	m_Timer->Start();

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));


	MeteorGrp::Init();

	m_MyGui->Get_RenderWindowLayout().Lights_Effect = true;
	m_MyGui->Get_RenderWindowLayout().Lights_Reset = true;
	changed = true;
}

Application::~Application()
{
	delete m_Camera;
	delete m_MyGui;
	delete m_City;
}

void Application::Update()
{
	MeteorGrp::Update();
	m_Timer->Update();
	m_FrameCounter->Update();
	m_Camera->Update();

	m_MyGui->Get_ViewPortLayout().ViewPort_TextureID = Renderer::Get_FrameBuffer()->Get_TextureId();
	m_MyGui->Get_RenderWindowLayout().Camera_Position = m_Camera->Get_CameraEye();
	m_MyGui->Get_DetailsWindowLayout().Network_details = RoadNetwork::NetworksToString();
	m_MyGui->Get_BuildWindowLayout().TextureID = Renderer::Get_Texture()->Get_TextureID();

	if (m_MyGui->Get_ViewPortLayout().ViewPort_Effect)
	{
		int width = m_MyGui->Get_ViewPortLayout().ViewPort_Width;
		int height = m_MyGui->Get_ViewPortLayout().ViewPort_Height;
		Renderer::Get_FrameBuffer()->Resize(width, height);
	}

	if (m_Timer->Tick())
	{
		int size = m_City->Get_CitizenSize();

		m_City->Simulate();

		m_MyGui->Get_GameWindowLayout().City_Money = m_City->Get_Money();
		m_MyGui->Get_GameWindowLayout().City_Satisfaction = 0;
		m_MyGui->Get_GameWindowLayout().Time_Game = m_City->Get_Time_Str();
		m_MyGui->Get_GameWindowLayout().Time_Real += m_Timer->Get_TickTime();

		//Meteor shooting
		if (rand() % 50 == 23)
		{
			int number = rand() % 5;
			if (rand() % 100000 == 666) number = 2500;

			for (int i = 0; i < number; i++)
			{
				MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
			}
		}

		changed = m_City->Get_CitizenSize() != size;
	}

	//NEW-GAME
	if (m_MyGui->Get_MenuBarLayout().NewGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().NewGame_Effect = false;
		m_MyGui->Get_GameWindowLayout().Time_Tick = m_MyGui->Get_MenuBarLayout().City_Time;
		m_Timer->Reset();
		m_Timer->SetTickTime(m_MyGui->Get_MenuBarLayout().City_Time);
		changed = true;

		MeteorGrp::Clear();
		RoadNetwork::ResetNetworks();
		City::Build_Log().clear();
		City::Build_Log().str("");
		City::Money_Log().clear();
		City::Money_Log().str("");
		City::Log_Changed() = true;
		Citizen::Log().clear();
		Citizen::Log().str("");
		Citizen::Log_Changed() = true;
		Renderer::ResizeShapeBuffers(m_MyGui->Get_MenuBarLayout().City_Size * m_MyGui->Get_MenuBarLayout().City_Size);

		delete m_City;
		m_City = new City(m_MyGui->Get_MenuBarLayout().City_Size, 800000);

		m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
		m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));
	}

	//LOAD-GAME
	if (m_MyGui->Get_MenuBarLayout().LoadGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().LoadGame_Effect = false;

		std::cout << "Load-Game" << std::endl;
		std::cout << "PATH: " << m_MyGui->Get_MenuBarLayout().LoadFile_Path << std::endl;
		std::cout << "NAME: " << m_MyGui->Get_MenuBarLayout().LoadFile_Name << std::endl;
	}

	//LOAD-GAME
	if (m_MyGui->Get_MenuBarLayout().SaveGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().SaveGame_Effect = false;

		std::cout << "Save-Game" << std::endl;
		std::cout << "PATH: " << m_MyGui->Get_MenuBarLayout().SaveFile_Path << std::endl;
		std::cout << "NAME: " << m_MyGui->Get_MenuBarLayout().SaveFile_Name << std::endl;
	}

	//GAME-TIME
	if (m_MyGui->Get_GameWindowLayout().Time_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Time_Effect = false;

		m_Timer->SetTickTime(m_MyGui->Get_GameWindowLayout().Time_Tick);
	}

	//GAME-CATASTROPHE
	if (m_MyGui->Get_GameWindowLayout().Catastrophe_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Catastrophe_Effect = false;

		for (int i = 0; i < m_MyGui->Get_GameWindowLayout().Catastrophe_Count; i++)
		{
			MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
		}
	}

	//GAME-TAX
	if (m_MyGui->Get_GameWindowLayout().Tax_Effect)
	{
		m_MyGui->Get_GameWindowLayout().Tax_Effect = false;

		m_City->SetTaxRate(RESIDENTIAL_LVL1, m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl1);
		m_City->SetTaxRate(RESIDENTIAL_LVL2, m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl2);
		m_City->SetTaxRate(RESIDENTIAL_LVL3, m_MyGui->Get_GameWindowLayout().ResidenceTaxLvl3);

		m_City->SetTaxRate(SERVICE_LVL1, m_MyGui->Get_GameWindowLayout().ServiceTaxLvl1);
		m_City->SetTaxRate(SERVICE_LVL2, m_MyGui->Get_GameWindowLayout().ServiceTaxLvl2);
		m_City->SetTaxRate(SERVICE_LVL3, m_MyGui->Get_GameWindowLayout().ServiceTaxLvl3);

		m_City->SetTaxRate(INDUSTRIAL_LVL1, m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl1);
		m_City->SetTaxRate(INDUSTRIAL_LVL2, m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl2);
		m_City->SetTaxRate(INDUSTRIAL_LVL3, m_MyGui->Get_GameWindowLayout().IndustrialTaxLvl3);
	}
	
	//RENDER-FRAME
	if (m_FrameCounter->Tick())
	{
		m_MyGui->Get_RenderWindowLayout().Frame_Fps = m_FrameCounter->Get_FPS();
		m_MyGui->Get_RenderWindowLayout().Frame_Time = m_FrameCounter->Get_DeltaTime();
		m_FrameCounter->Reset();
	}

	//RENDER-CAMERA
	if (m_MyGui->Get_RenderWindowLayout().Camera_Effect)
	{
		m_MyGui->Get_RenderWindowLayout().Camera_Effect = false;

		m_Camera->Set_Mode(m_MyGui->Get_RenderWindowLayout().Camera_Mode, 0, 0);
		m_Camera->Get_Speed() = m_MyGui->Get_RenderWindowLayout().Camera_Speed;
	}

	//RENDER-LIGHTS
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
		m_MyGui->Get_RenderWindowLayout().Lights_Reset  = false;
	}

	//LOG
	if (City::Log_Changed() || Citizen::Log_Changed())
	{
		m_MyGui->Get_LogWindowLayout().build_log   = City::Build_Log().str();
		m_MyGui->Get_LogWindowLayout().citizen_log = Citizen::Log().str();
		m_MyGui->Get_LogWindowLayout().money_log   = City::Money_Log().str();
		Citizen::Log_Changed() = false;
		City::Log_Changed() = false;
	}

	//BUILD - OR MOUSE EVENT
	if (m_MyGui->Get_EventLayout().Hit)
	{
		m_MyGui->Get_EventLayout().Hit = false;
		ConvertMouseInputTo3D(m_MyGui->Get_EventLayout().Mouse_X, m_MyGui->Get_EventLayout().Mouse_Y, Renderer::Get_FrameBuffer()->Get_FrameWidth(), Renderer::Get_FrameBuffer()->Get_FrameHeight());
		
		if (m_MyGui->Get_BuildWindowLayout().Build_Id == -1) //CHECK DETAILS
		{
			m_MyGui->Get_DetailsWindowLayout().Field_IsZone = false;
			m_MyGui->Get_DetailsWindowLayout().Field_Type = m_City->Get_GameField(HitX, HitY)->Get_Type();
			m_MyGui->Get_DetailsWindowLayout().Field_Coord_x = HitX;
			m_MyGui->Get_DetailsWindowLayout().Field_Coord_y = HitY;

			if (m_City->Get_GameField(HitX, HitY)->IsZone())
			{
				Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(HitX, HitY));
				m_MyGui->Get_DetailsWindowLayout().Field_IsZone = true;
				m_MyGui->Get_DetailsWindowLayout().Field_Satisfaction = zone->Get_RawSatisfaction();
				m_MyGui->Get_DetailsWindowLayout().Field_Level = zone->Get_ZoneDetails().level + 1;
				m_MyGui->Get_DetailsWindowLayout().Field_Contain = zone->Get_ZoneDetails().contain;
				m_MyGui->Get_DetailsWindowLayout().Field_Capacity = zone->Get_ZoneDetails().capacity;
				m_MyGui->Get_DetailsWindowLayout().Citizens_details = zone->Get_CitizenDetails();
			}
		}

		else if (m_MyGui->Get_BuildWindowLayout().Build_Id == -2)
		{
			if (m_City->Get_GameField(HitX, HitY)->IsZone())
			{
				Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(HitX, HitY));

				m_MyGui->Get_DetailsWindowLayout().Field_Type = m_City->Get_GameField(HitX, HitY)->Get_Type();
				m_MyGui->Get_DetailsWindowLayout().Field_Coord_x = HitX;
				m_MyGui->Get_DetailsWindowLayout().Field_Coord_y = HitY;

				m_MyGui->Get_DetailsWindowLayout().Upgrade_Show = true;
				m_MyGui->Get_DetailsWindowLayout().level = zone->Get_Level();

				std::cout << "LEVEL: " << m_MyGui->Get_DetailsWindowLayout().level << std::endl;
			}
		}

		else if (m_MyGui->Get_BuildWindowLayout().Build_Id == -3)
		{
			//TODO: DEGRADE
		}

		else 
		{
			FieldType type = (FieldType)m_MyGui->Get_BuildWindowLayout().Build_Id;
			FieldDirection dir = (FieldDirection)(m_MyGui->Get_EventLayout().Rotate % 4);

			if (m_City->IsBuildable(type, dir, HitX, HitY))
			{
				std::cout << ">> BUILDING PLACED" << std::endl;
				m_City->Set_GameTableValue(HitX, HitY, type, dir);
				changed = true;
			}
			else
			{
				std::cout << ">> NOT BUILDABLE" << std::endl;
			}
		}
	}

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

	if (m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect)
	{
		m_City->UpgradeField(m_MyGui->Get_DetailsWindowLayout().Field_Coord_x, m_MyGui->Get_DetailsWindowLayout().Field_Coord_y);
		m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect = false;
		changed = true;

		std::cout << "UPGRADED" << std::endl;
	}
}

void Application::RenderUI()
{
	m_MyGui->Pre_Render();

	m_MyGui->DockSpace();

	m_MyGui->Post_Render();
}

void Application::Render()
{
	if (changed)
	{
		std::unordered_set<GameField*> fields_2x2;
		for (int i = 0; i < m_City->Get_GameTableSize(); i++)
		{
			for (int j = 0; j < m_City->Get_GameTableSize(); j++)
			{
				int type = m_City->Get_GameField(i, j)->Get_Type();
				int amount = 1;

				if (m_City->Get_GameField(i, j)->IsZone())
				{
					Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(i, j));
					if (type == RESIDENTIAL_LVL1) amount = zone->Get_ZoneDetails().contain;
					if (type == RESIDENTIAL_LVL2) amount = zone->Get_ZoneDetails().contain / 2 + zone->Get_ZoneDetails().contain % 2;
					if (type == RESIDENTIAL_LVL3) amount = zone->Get_ZoneDetails().contain / 8 + (zone->Get_ZoneDetails().contain % 8 == 0 ? 0 : 1);
					if (type == INDUSTRIAL_LVL1) amount = zone->Get_ZoneDetails().contain;
					if (type == INDUSTRIAL_LVL2) amount = zone->Get_ZoneDetails().contain;
					if (type == INDUSTRIAL_LVL3) amount = zone->Get_ZoneDetails().contain;
					if (type == SERVICE_LVL1) amount = zone->Get_ZoneDetails().contain;
					if (type == SERVICE_LVL2) amount = zone->Get_ZoneDetails().contain / 2 + zone->Get_ZoneDetails().contain % 2;
					if (type == SERVICE_LVL3) amount = zone->Get_ZoneDetails().contain / 4 + (zone->Get_ZoneDetails().contain % 4 == 0 ? 0 : 1);
				}

				if (m_City->Get_GameField(i, j)->IsForest())
				{
					Forest* zone = dynamic_cast<Forest*>(m_City->Get_GameField(i, j));
					amount = zone->age;
				}

				if (type == UNIVERSITY || type == STADIUM || type == HIGHSCHOOL)
				{
					if (fields_2x2.find(m_City->Get_GameField(i, j)) != fields_2x2.end()) continue;
					fields_2x2.insert(m_City->Get_GameField(i, j));
				}

				Renderer::AddShapeTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_FieldDirection(), amount);
				Renderer::AddGroundTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_FieldDirection(), type == ROAD ? DetermineRoadTextureID(i, j) : Renderer::DetermineGroundTextureID((RenderShapeType)type));
			}
		}
		Renderer::Changed = true;
		changed = false;
	}

	Renderer::PreRender();
	Renderer::SceneRender(INSTANCED);

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

void Application::Window_ResizedEvent(int width, int height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
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

		HitX = (int)rayz;
		HitY = (int)rayx;
	}

}

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
		return 6; //Keresztez�d�s
	}
	else if ((upper_field && !lower_field && !right_field && !left_field) || (!upper_field && lower_field && !right_field && !left_field) || (upper_field && lower_field && !right_field && !left_field))
	{
		return 7; //�tmen� fel-le
	}
	else if ((!upper_field && !lower_field && right_field && !left_field) || (!upper_field && !lower_field && !right_field && left_field) || (!upper_field && !lower_field && right_field && left_field))
	{
		return 107; //�tmen� jobbra-balra
	}
	else if ((upper_field && !lower_field && right_field && left_field))
	{
		return 5; //H�rom �g� balra-fel-jobbra
	}
	else if ((!upper_field && lower_field && right_field && left_field))
	{
		return 205; //H�rom �g� balra-le-jobbra
	}
	else if ((upper_field && lower_field && right_field && !left_field))
	{
		return 305;//H�rom �g� jobbra-fel-le
	}
	else if ((upper_field && lower_field && !right_field && left_field))
	{
		return 105;//H�rom �g� balra-fel-le
	}
	else if ((!upper_field && lower_field && right_field && !left_field))
	{
		return 104;//kanyar lentr�l-jobbra
	}
	else if ((!upper_field && lower_field && !right_field && left_field))
	{
		return 4;//kanyar lentr�l-balra
	}
	else if ((upper_field && !lower_field && !right_field && left_field))
	{
		return 304;//kanyar balr�l-felfele
	}
	else if ((upper_field && !lower_field && right_field && !left_field))
	{
		return 204;//kanyar jobbr�l-felfele
	}
	else
	{
		return 7;
	}
}