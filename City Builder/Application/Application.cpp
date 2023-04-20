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

	m_MyGui = new MyGui(m_Camera);
	m_FrameCounter = new FrameCounter();
	m_Timer = new Timer(0.1);
	m_Timer->Start();

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));


	MeteorGrp::Init();

	m_MyGui->Get_LightsLayout().effect = true;
	m_MyGui->Get_LightsLayout().reset = true;
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

	if (m_Timer->Tick())
	{
		int size = m_City->Get_CitizenSize();

		m_City->Simulate();
		m_MyGui->Get_CityLayout().money = m_City->Get_Money();
		m_MyGui->Get_CityLayout().time = m_City->Get_Time_Str();

		//Meteor shooting
		if (rand() % 50 == 23)
		{
			int number = rand() % 5;
			if (rand() % 1000 == 666) number = 2500;

			for (int i = 0; i < number; i++)
			{
				MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
			}
		}

		changed = m_City->Get_CitizenSize() != size;
	}

	if (m_FrameCounter->Tick())
	{
		m_MyGui->Get_RenderWindowLayout().fps = m_FrameCounter->Get_FPS();
		m_MyGui->Get_RenderWindowLayout().time = m_FrameCounter->Get_DeltaTime();
		m_FrameCounter->Reset();
	}

	if (m_MyGui->Get_NewGameLayout().effect) 
	{
		MeteorGrp::Clear();

		m_City = new City(m_MyGui->Get_NewGameLayout().size, 10000);
		RoadNetwork::ResetNetworks();
		Citizen::Log().str("");
		Citizen::Log().clear();
		Citizen::Log_Changed() = true;

		m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
		m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));

		m_MyGui->Get_NewGameLayout().effect = false;
		changed = true;
	}

	if (m_MyGui->Get_LoadGameLayout().effect)
	{
		std::cout << "Load-Game" << std::endl;
		std::cout << m_MyGui->Get_LoadGameLayout().path << std::endl;
		std::cout << m_MyGui->Get_LoadGameLayout().name << std::endl;

		m_MyGui->Get_LoadGameLayout().effect = false;
	}
	
	if (m_MyGui->Get_SaveGameLayout().effect)
	{
		std::cout << "Save-Game" << std::endl;
		std::cout << m_MyGui->Get_SaveGameLayout().path << std::endl;
		std::cout << m_MyGui->Get_SaveGameLayout().name << std::endl;

		m_MyGui->Get_SaveGameLayout().effect = false;
	}

	if (m_MyGui->Get_TaxLayout().effect)
	{
		m_City->SetTaxRate(RESIDENTIAL_LVL1, m_MyGui->Get_TaxLayout().ResidenceTaxLvl1);
		m_City->SetTaxRate(RESIDENTIAL_LVL2, m_MyGui->Get_TaxLayout().ResidenceTaxLvl2);
		m_City->SetTaxRate(RESIDENTIAL_LVL3, m_MyGui->Get_TaxLayout().ResidenceTaxLvl3);

		m_City->SetTaxRate(SERVICE_LVL1, m_MyGui->Get_TaxLayout().ServiceTaxLvl1);
		m_City->SetTaxRate(SERVICE_LVL2, m_MyGui->Get_TaxLayout().ServiceTaxLvl2);
		m_City->SetTaxRate(SERVICE_LVL3, m_MyGui->Get_TaxLayout().ServiceTaxLvl3);

		m_City->SetTaxRate(INDUSTRIAL_LVL1, m_MyGui->Get_TaxLayout().IndustrialTaxLvl1);
		m_City->SetTaxRate(INDUSTRIAL_LVL2, m_MyGui->Get_TaxLayout().IndustrialTaxLvl2);
		m_City->SetTaxRate(INDUSTRIAL_LVL3, m_MyGui->Get_TaxLayout().IndustrialTaxLvl3);

		m_MyGui->Get_TaxLayout().effect = false;
	}

	if (m_MyGui->Get_LightsLayout().effect)
	{
		LightProperties r_LightProperties;
		r_LightProperties.lightDir    = m_MyGui->Get_LightsLayout().reset ? glm::vec3(1, -1, 1) : m_MyGui->Get_LightsLayout().lightDir;
		r_LightProperties.specularPow = m_MyGui->Get_LightsLayout().reset ? 64 : m_MyGui->Get_LightsLayout().specularPow;
		r_LightProperties.La = m_MyGui->Get_LightsLayout().reset ? glm::vec3(0.5, 0.5, 0.5) : m_MyGui->Get_LightsLayout().La;
		r_LightProperties.Ld = m_MyGui->Get_LightsLayout().reset ? glm::vec3(1, 1, 0.85) : m_MyGui->Get_LightsLayout().Ld;
		r_LightProperties.Ls = m_MyGui->Get_LightsLayout().reset ? glm::vec3(1, 1, 1) : m_MyGui->Get_LightsLayout().Ls;
		r_LightProperties.Ka = m_MyGui->Get_LightsLayout().reset ? glm::vec3(0.8, 0.8, 0.8) : m_MyGui->Get_LightsLayout().Ka;
		r_LightProperties.Kd = m_MyGui->Get_LightsLayout().reset ? glm::vec3(1, 1, 1) : m_MyGui->Get_LightsLayout().Kd;
		r_LightProperties.Ks = m_MyGui->Get_LightsLayout().reset ? glm::vec3(0.7, 0.6, 0.6) : m_MyGui->Get_LightsLayout().Ks;
		Renderer::Set_LightProperties(r_LightProperties);

		m_MyGui->Get_LightsLayout().effect = false;
		m_MyGui->Get_LightsLayout().reset = false;
	}

	//------------------------------
	
	if (m_MyGui->hit)
	{
		m_MyGui->hit = false;
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, Renderer::Get_FrameBuffer()->Get_FrameWidth(), Renderer::Get_FrameBuffer()->Get_FrameHeight());

		if (m_MyGui->Get_BuildLayout().building == -1)
		{
			m_MyGui->Get_FieldDetailsLayout().isZone = false;
			m_MyGui->Get_FieldDetailsLayout().x = HitX;
			m_MyGui->Get_FieldDetailsLayout().y = HitY;

			if (m_City->Get_GameField(HitX, HitY)->IsZone())
			{
				Zone* zone = dynamic_cast<Zone*>(m_City->Get_GameField(HitX, HitY));
				m_MyGui->Get_FieldDetailsLayout().isZone = true;
				m_MyGui->Get_FieldDetailsLayout().satisfaction = RoadNetwork::GetSatisfaction(zone);
				m_MyGui->Get_FieldDetailsLayout().citizens_details = zone->Get_CitizenDetails();
				m_MyGui->Get_FieldDetailsLayout().level = zone->Get_ZoneDetails().level + 1;
				m_MyGui->Get_FieldDetailsLayout().contain = zone->Get_ZoneDetails().contain;
				m_MyGui->Get_FieldDetailsLayout().capacity = zone->Get_ZoneDetails().capacity;
			}
		}
		else 
		{
			GameField* field = m_City->Get_GameField(HitX, HitY);
			m_City->Set_GameTableValue(HitX, HitY, (FieldType)m_MyGui->Get_BuildLayout().building, (FieldDirection)(m_MyGui->r % 4));
			changed = true;
		}

	}

	if (City::Log_Changed() || Citizen::Log_Changed())
	{
		m_MyGui->Get_LogLayout().build_log = City::Build_Log().str();
		m_MyGui->Get_LogLayout().citizen_log = Citizen::Log().str();
		m_MyGui->Get_LogLayout().money_log = City::Money_Log().str();
		Citizen::Log_Changed() = false;
		City::Log_Changed() = false;
	}

	if (m_MyGui->Get_CatastropheLayout().effect)
	{
		m_MyGui->Get_CatastropheLayout().effect = false;
		for (int i = 0; i < m_MyGui->Get_CatastropheLayout().count; i++)
		{
			MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
		}
	}

	if (MeteorGrp::Effect())
	{
		auto fields = MeteorGrp::Change();

		for (auto field : fields)
		{
			if(field.second != 49)
				m_City->Set_GameTableValue(field.first, field.second, CRATER, (FieldDirection)LEFT);
			changed = true;
		}

		MeteorGrp::Delete();
	}

	if (m_MyGui->Get_DimensionLayout().effect)
	{
		m_MyGui->Get_DimensionLayout().effect = false;
		m_Camera->Set_Mode(m_MyGui->Get_DimensionLayout().dimension, 0, 0);
	}
}

void Application::RenderUI()
{
	m_MyGui->Pre_Render();

	m_MyGui->DockSpace();
	m_MyGui->Demo_Window();
	m_MyGui->Build_Window(Renderer::Get_Texture());
	m_MyGui->GameDetails_Window();
	m_MyGui->GameOptions_Window();
	m_MyGui->RenderOptions_Window();
	m_MyGui->FieldDetails_Window();
	m_MyGui->CityDetials_Window();
	m_MyGui->Log_Window();
	//m_MyGui->GameIdk();
	m_MyGui->ViewPort_Render(Renderer::Get_FrameBuffer());

	m_MyGui->Post_Render();
}

void Application::Render()
{
	if (changed)
	{
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

				Renderer::AddShapeTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_FieldDirection(), amount);
				Renderer::AddGroundTransforms(i, j, type == ROAD ? DetermineRoadTextureID(i, j) : Renderer::DetermineGroundTextureID((RenderShapeType)type));
			}
		}
		Renderer::Changed = true;
		changed = false;
	}

	Renderer::PreRender();
	Renderer::SceneRender(INSTANCED);

	if (m_MyGui->BuildHover)
	{
		ConvertMouseInputTo3D(m_MyGui->mouse_x, m_MyGui->mouse_y, (int)m_MyGui->content_size.x, (int)m_MyGui->content_size.y);

		bool l1 = HitX >= 0 && HitX < m_City->Get_GameTableSize();
		bool l2 = HitY >= 0 && HitY < m_City->Get_GameTableSize();

		if (l1 && l2)
		{
			Renderer::Buildable = m_City->Get_GameField(HitX, HitY)->IsEmpty();
			Renderer::RenderNormal((RenderShapeType)m_MyGui->Get_BuildLayout().building, HitX, HitY, (m_MyGui->r % 4));
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
		return 6; //Keresztezõdés
	}
	else if ((upper_field && !lower_field && !right_field && !left_field) || (!upper_field && lower_field && !right_field && !left_field) || (upper_field && lower_field && !right_field && !left_field))
	{
		return 7; //Átmenõ fel-le
	}
	else if ((!upper_field && !lower_field && right_field && !left_field) || (!upper_field && !lower_field && !right_field && left_field) || (!upper_field && !lower_field && right_field && left_field))
	{
		return 107; //Átmenõ jobbra-balra
	}
	else if ((upper_field && !lower_field && right_field && left_field))
	{
		return 5; //Három ágú balra-fel-jobbra
	}
	else if ((!upper_field && lower_field && right_field && left_field))
	{
		return 205; //Három ágú balra-le-jobbra
	}
	else if ((upper_field && lower_field && right_field && !left_field))
	{
		return 305;//Három ágú jobbra-fel-le
	}
	else if ((upper_field && lower_field && !right_field && left_field))
	{
		return 105;//Három ágú balra-fel-le
	}
	else if ((!upper_field && lower_field && right_field && !left_field))
	{
		return 104;//kanyar lentrõl-jobbra
	}
	else if ((!upper_field && lower_field && !right_field && left_field))
	{
		return 4;//kanyar lentrõl-balra
	}
	else if ((upper_field && !lower_field && !right_field && left_field))
	{
		return 304;//kanyar balról-felfele
	}
	else if ((upper_field && !lower_field && right_field && !left_field))
	{
		return 204;//kanyar jobbról-felfele
	}
	else
	{
		return 7;
	}
}