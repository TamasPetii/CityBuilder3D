#include "Application.h"

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

void Application::NewGame(int size, int money = -1, int time = -1) {
	m_MyGui->Get_DetailsWindowLayout().Details_X = 0;
	m_MyGui->Get_DetailsWindowLayout().Details_Y = 0;
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
	for (auto& it : taxRates) {
		*it.second = 40;
	}
	m_MyGui->Get_GameWindowLayout().Tax_Effect = true;

	m_Camera->Set_Eye(glm::vec3(m_City->Get_GameTableSize(), 5, m_City->Get_GameTableSize() + 5));
	m_Camera->Set_At(glm::vec3(m_City->Get_GameTableSize(), 0, m_City->Get_GameTableSize()));
}

void Application::LoadGame() {
	std::ifstream saveFile(m_MyGui->Get_MenuBarLayout().LoadFile_Path);

	if (!saveFile.is_open())
	{
		std::cout << "Could not open [" << m_MyGui->Get_MenuBarLayout().LoadFile_Path << "]" << std::endl;
		return;
	}

	int size, tmp, money, time;
	saveFile >> size >> money >> time;
	Application::NewGame(size, money, time);

	auto taxRates = Application::Get_TaxRates();
	for (auto& it : taxRates) {
		int type;
		float taxRate;
		saveFile >> type >> taxRate;
		m_City->Set_TaxRate(static_cast<FieldType>(type), taxRate);
		*it.second = taxRate;
	}

	//mezõk
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int type_i, dir_i;
			saveFile >> type_i >> dir_i;
			FieldType type = static_cast<FieldType>(type_i);
			FieldDirection dir = static_cast<FieldDirection>(dir_i);
			if (type == FOREST) {
				int tmp;
				saveFile >> tmp;
				m_City->Set_GameTableValue(i, j, type, dir);
				GameField* f = m_City->Get_GameField(i, j);
				dynamic_cast<Forest*>(f)->Set_Age(tmp);
			}
			else if (type != EMPTY) {
				m_City->Set_GameTableValue(i, j, type, dir);
			}
		}
	}

	//polgárok
	int citizenSize, x, y;
	saveFile >> citizenSize;
	for (int i = 0; i < citizenSize; i++) {
		Citizen* citizen = new Citizen();
		saveFile >> x >> y;
		citizen->JoinZone(dynamic_cast<Zone*>(m_City->Get_GameField(x, y)));//lakóhely
		saveFile >> x >> y;
		if (x != -1 && y != -1) {
			citizen->JoinZone(dynamic_cast<Zone*>(m_City->Get_GameField(x, y)));//munkahely
		}
		saveFile >> x >> y;
		citizen->Set_Age(x);
		citizen->Set_Education(static_cast<Education>(y));
		saveFile >> x >> y;
		citizen->Set_MonthsBeforePension(x);
		citizen->Set_Pension(y);
	}
}

void Application::SaveGame() {
	std::ofstream saveFile(m_MyGui->Get_MenuBarLayout().SaveFile_Path + ".txt");

	if (!saveFile.is_open())
	{
		std::cout << "Could not open [" << m_MyGui->Get_MenuBarLayout().SaveFile_Path + ".txt" << "]" << std::endl;
		return;
	}

	//Város adatai
	int size = m_City->Get_GameTableSize();
	saveFile << size << std::endl;
	saveFile << m_City->Get_Money() << std::endl;
	saveFile << m_City->Get_Time() << std::endl;

	auto taxRates = Application::Get_TaxRates();
	for (auto& it : taxRates) {
		saveFile << it.first << " " << *it.second << " ";
	}
	saveFile << std::endl;

	//Mezõk
	std::unordered_set<GameField*> bigBuildings;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			GameField* field = m_City->Get_GameField(i, j);
			FieldType type = field->Get_Type();
			if (type == UNIVERSITY || type == HIGHSCHOOL || type == POWERSTATION || type == STADIUM) {
				if (bigBuildings.find(field) == bigBuildings.end()) {
					bigBuildings.emplace(field);
					if (type == HIGHSCHOOL) {
						saveFile << type << " " << field->Get_Direction() << " ";
						continue;
					}
				}
				else {
					saveFile << EMPTY << " " << 0 << " ";
					continue;
				}
			}
			else if (type == FOREST) {
				saveFile << type << " " << field->Get_Direction() << " " << dynamic_cast<Forest*>(field)->Get_Age() << " ";
				continue;
			}
			saveFile << type << " " << field->Get_Direction() << " ";
		}
		saveFile << std::endl;
	}

	//Polgárok
	saveFile << m_City->Get_CitizenSize() << std::endl;
	for (auto& citizen : m_City->Get_Citizens()) {
		saveFile << citizen->Get_Residence()->Get_X() << " " << citizen->Get_Residence()->Get_Y() << " ";
		if (citizen->Get_Workplace() == nullptr) {
			saveFile << -1 << " " << -1 << " ";
		}
		else {
			saveFile << citizen->Get_Workplace()->Get_X() << " " << citizen->Get_Workplace()->Get_Y() << " ";
		}
		saveFile << citizen->Get_Age() << " " << citizen->Get_Education() << " ";
		saveFile << citizen->Get_MonthsBeforePension() << " " << citizen->Get_Pension() << std::endl;
	}
}

std::vector<std::pair<FieldType, float*>> Application::Get_TaxRates() {
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

void Application::Update()
{
	if (m_MyGui->UI_MODE == LOBBY)
	{
		m_Camera->Set_Eye(glm::vec3(50.f * cosf(glfwGetTime() * 2 * M_PI / 250) + m_City->Get_GameTableSize(), 25.f, 50.f * sinf(glfwGetTime() * 2 * M_PI / 250) + m_City->Get_GameTableSize()));
		m_MyGui->Get_ViewPortLayout().ViewPort_TextureID = Renderer::Get_FrameBuffer()->Get_TextureId();

		if (m_MyGui->Get_ViewPortLayout().ViewPort_Effect)
		{
			int width = m_MyGui->Get_ViewPortLayout().ViewPort_Width;
			int height = m_MyGui->Get_ViewPortLayout().ViewPort_Height;
			Renderer::Get_FrameBuffer()->Resize(width, height);
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
			m_MyGui->Get_RenderWindowLayout().Lights_Reset = false;
		}
	}
	else 
	{
		MeteorGrp::Update();
		CarGroup::Update();
		CheckCarPos();
		m_Timer->Update();
		m_FrameCounter->Update();
		m_Camera->Update();
		FireTruckSimulation();

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
			m_MyGui->Get_GameWindowLayout().City_Satisfaction = m_City -> Get_CombinedHappiness();
			m_MyGui->Get_GameWindowLayout().Time_Game = m_City->Get_TimeStr();
			m_MyGui->Get_GameWindowLayout().Time_Real += m_Timer->Get_TickTime();

			//Meteor shooting
			if (rand() % 500 == 23)
			{
				int number = rand() % 5;
				if (rand() % 100000 == 666) number = 2500;

				for (int i = 0; i < number; i++)
				{
					MeteorGrp::Add(rand() % m_City->Get_GameTableSize(), rand() % m_City->Get_GameTableSize());
				}
			}

			//Cars
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

		for (auto it = truck_map.begin(); it != truck_map.end(); it++)
		{
			m_City->Get_GameField(it->second->endY / 2, it->second->endX / 2)->FireCounter += 2;

			if (m_City->Get_GameField(it->second->endY / 2, it->second->endX / 2)->FireCounter >= 500)
			{
				m_City->Get_GameField(it->second->endY / 2, it->second->endX / 2)->FireCounter = 500;
				m_City->Get_GameField(it->second->endY / 2, it->second->endX / 2)->OnFire() = false;
				changed = true;
			}
		}

		changed = changed || m_City->Get_CitizenSize() != size;
	}

	//NEW-GAME
	if (m_MyGui->Get_MenuBarLayout().NewGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().NewGame_Effect = false;
		Application::NewGame(m_MyGui->Get_MenuBarLayout().City_Size);
	}

	//LOAD-GAME
	if (m_MyGui->Get_MenuBarLayout().LoadGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().LoadGame_Effect = false;
		Application::LoadGame();
	}

	//SAVE-GAME
	if (m_MyGui->Get_MenuBarLayout().SaveGame_Effect)
	{
		m_MyGui->Get_MenuBarLayout().SaveGame_Effect = false;
		Application::SaveGame();
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
		std::vector<std::pair<FieldType, float*>> taxRates = Application::Get_TaxRates();

		for (auto& it : taxRates) {
			m_City->Set_TaxRate(it.first, *it.second);
		}
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
		if (true)
		{
			m_MyGui->Get_LogWindowLayout().build_log   = City::BUILD_LOG.str();
			m_MyGui->Get_LogWindowLayout().citizen_log = Citizen::LOG.str();
			m_MyGui->Get_LogWindowLayout().money_log   = City::MONEY_LOG.str();
		}

		//Detials
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

		//BUILD - OR MOUSE EVENT
		if (m_MyGui->Get_EventLayout().Hit)
		{
			m_MyGui->Get_EventLayout().Hit = false;
			ConvertMouseInputTo3D(m_MyGui->Get_EventLayout().Mouse_X, m_MyGui->Get_EventLayout().Mouse_Y, Renderer::Get_FrameBuffer()->Get_FrameWidth(), Renderer::Get_FrameBuffer()->Get_FrameHeight());

			if (m_MyGui->Get_BuildWindowLayout().Build_Id == -1) //CHECK DETAILS
			{
				m_MyGui->Get_DetailsWindowLayout().Details_X = HitX;
				m_MyGui->Get_DetailsWindowLayout().Details_Y = HitY;
			}

			else if (m_MyGui->Get_BuildWindowLayout().Build_Id == -2)
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

			else if (m_MyGui->Get_BuildWindowLayout().Build_Id == -3)
			{
				GameField* field = m_City->Get_GameField(HitX, HitY);
				if ((field->IsZone() || field->IsBuilding()) && field->Get_Type() != FIRESTATION)
				{
					field->OnFire() = true;
					changed = true;
				}
			}

			else if (m_MyGui->Get_BuildWindowLayout().Build_Id == -4)
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

			else 
			{
				FieldType type = (FieldType)m_MyGui->Get_BuildWindowLayout().Build_Id;
				FieldDirection dir = (FieldDirection)(m_MyGui->Get_EventLayout().Rotate % 4);

				if (m_City->IsBuildable(type, dir, HitX, HitY))
				{

					FieldType oldType = m_City->Get_GameField(HitX, HitY)->Get_Type();
					m_City->Set_GameTableValue(HitX, HitY, type, dir);
					FieldType newType = m_City->Get_GameField(HitX, HitY)->Get_Type();

					if (oldType != newType && (oldType == ROAD || newType == ROAD))
					{
						//TODO: Delete only the cars which are affected by the new road
						//CarGroup::Clear();
					}

					changed = true;
				}
			}
		}

		//METEOR HITS GROUND
		if (MeteorGrp::Effect())
		{
			auto fields = MeteorGrp::Change();

			for (auto field : fields)
			{
				if (m_City->Get_GameField(field.first, field.second)->Get_Type() == ROAD)
				{
					//TODO: Delete only the cars which are affected by the deleted road
					CarGroup::Clear();
				}
				m_City->Set_GameTableValue(field.first, field.second, CRATER, (FieldDirection)LEFT);
				changed = true;
			}

			MeteorGrp::Delete();
		}
		if (m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect)
		{
			m_City->UpgradeField(m_MyGui->Get_DetailsWindowLayout().Field_X, m_MyGui->Get_DetailsWindowLayout().Field_Y);
			m_MyGui->Get_DetailsWindowLayout().Upgrade_Effect = false;
			changed = true;
		}
	}


}

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

void Application::Render()
{
	if (changed || Zone::CHANGED || City::CHANGED)
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
					if (type == RESIDENTIAL_LVL1) amount = zone->Get_Contain();
					if (type == RESIDENTIAL_LVL2) amount = zone->Get_Contain() / 2 + zone->Get_Contain() % 2;
					if (type == RESIDENTIAL_LVL3) amount = zone->Get_Contain() / 8 + (zone->Get_Contain() % 8 == 0 ? 0 : 1);
					if (type == INDUSTRIAL_LVL1) amount = zone->Get_Contain();
					if (type == INDUSTRIAL_LVL2) amount = zone->Get_Contain();
					if (type == INDUSTRIAL_LVL3) amount = zone->Get_Contain();
					if (type == SERVICE_LVL1) amount = zone->Get_Contain();
					if (type == SERVICE_LVL2) amount = zone->Get_Contain() / 2 + zone->Get_Contain() % 2;
					if (type == SERVICE_LVL3) amount = zone->Get_Contain() / 4 + (zone->Get_Contain() % 4 == 0 ? 0 : 1);
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
				Renderer::AddGroundTransforms((RenderShapeType)type, i, j, m_City->Get_GameField(i, j)->Get_Direction(), type == ROAD ? DetermineRoadTextureID(i, j) : m_City->Get_GameField(i, j)->OnFire() ? 68 : Renderer::DetermineGroundTextureID((RenderShapeType)type, contain));
			}
		}

		Renderer::Changed = true;
		Zone::CHANGED = false;
		City::CHANGED = false;
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

void Application::FireTruckSimulation()
{
	std::vector<Car*> to_delete_CARGROUP;
	std::vector<Car*> to_delete_MAP;

	for (auto truck : CarGroup::m_FireTrucks)
	{
		float dir = 0.02 * cos(truck->Get_Rotation());

		float rotation = 0;
		float start_x = truck->Get_CurrentPosition(rotation).x + dir;
		float start_y = truck->Get_CurrentPosition(rotation).z + dir;

		int table_x = start_y / 2.f;
		int table_y = start_x / 2.f;

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

	for (auto truck : CarGroup::m_FireTrucks)
	{
		if (truck->ShouldBeDeleted() && truck_map.find(truck) == truck_map.end())
		{
			float dir = 0.02 * cos(truck->Get_Rotation());

			float rotation = 0;
			float start_x = truck->Get_CurrentPosition(rotation).x + dir;
			float start_y = truck->Get_CurrentPosition(rotation).z + dir;

			int table_x = start_y / 2.f;
			int table_y = start_x / 2.f;

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
				CarGroup::m_FireTrucks.erase(truck);
			}
		}
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
						it->second = new WaterGroup(start_x, start_y, 2 * (y + j) + 1, 2 * (x + i) + 1);
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
					std::uniform_int_distribution<> distr(0, onFireFields.size() - 1);

					auto beginIT = onFireFields.begin();
					std::advance(beginIT, distr(gen));

					int randomField = *beginIT;
					
					it->second = new WaterGroup(start_x, start_y, 2 * (randomField % m_City->Get_GameTableSize()) + 1, 2 * (randomField / m_City->Get_GameTableSize()) + 1);
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

void Application::CheckCarPos()
{
	for (auto car : CarGroup::m_Cars)
	{
		float rotation = 0;
		float start_x = car->Get_CurrentPosition(rotation).x;
		float start_y = car->Get_CurrentPosition(rotation).z;

		int table_x = start_y / 2.f;
		int table_y = start_x / 2.f;

		FieldType type = m_City->Get_GameField(table_x, table_y)->Get_Type();

		if (type == EMPTY || type == CRATER)
		{

			CarGroup::m_Cars.erase(car);

			std::vector<CarAndCoord*> to_delete;

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
}