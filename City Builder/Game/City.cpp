#include "City.h"
#include <stdlib.h> 
#include <time.h>
#include <random>

std::stringstream City::BUILD_LOG;
std::stringstream City::MONEY_LOG;

City::City(int size)
{
	m_GameTable = new GameTable(size);
	m_Money = 0;
	UpdateMoney(5000000); //This will set money satisfaction in citizen
	GenerateForests(5, 0.4);
	GenerateLakes(5, 0.4);
}

std::string City::Get_TimeStr() const
{
	return std::to_string(Get_Year()) + "." + std::to_string(Get_Month()) + "." + std::to_string(Get_Day());
}

GameField* City::Get_GameField(int x, int y) const
{
	if (!m_GameTable->ValidateCoordinate(x, y)) return nullptr;

	return m_GameTable->Get_TableValue(x, y);
}

void City::Simulate()
{
	HandleRecalculation();
	CalculateHappiness();
	GenerateCitizens(rand() % 2 == 0 ? rand() % 3 : 0);
	HandleLosingZone();

	++m_DailyTickCounter;

	if (m_DailyTickCounter != 0 && m_DailyTickCounter % 30 == 0)
	{
		CollectMonthlyTax();
	}

	if (m_DailyTickCounter != 0 && m_DailyTickCounter % 360 == 0)
	{
		CollectAnnualCosts();
		SimulatePopulationAging();
	}
}

void City::UpdateMoney(float amount)
{
	m_Money += amount;

	Citizen::MONEY_SATISFACTION = m_Money;
}

float City::CalculateMonthlyTax()
{
	float tax = 0;
	for (Citizen* citizen : m_Citizens)
	{
		tax += citizen->PayTax();
	}
	return tax;
}

void City::CollectMonthlyTax()
{
	float tax = CalculateMonthlyTax();
	UpdateMoney(tax);

	MONEY_LOG << ((tax >= 0) ? "+ " : "- ") << tax << "$ >> Monthly Tax {" << Get_TimeStr() << "}" << std::endl;
}

void City::CollectAnnualCosts()
{
	float cost = m_GameTable->Get_TotalAnnualCost();
	UpdateMoney(-cost);

	MONEY_LOG << "- " << cost << "$ >> Annual Cost {" << Get_TimeStr() << "}" << std::endl;
}

void City::HandleRecalculation() {
	if (m_GameTable->recalculate) {
		for (auto& citizen : m_Citizens) {
			Zone* residence = citizen->Get_Residence();
			Zone* workplace = citizen->Get_Workplace();
			if (residence == nullptr || workplace == nullptr) continue;

			if (!RoadNetwork::IsConnected(residence, workplace)) {
				citizen->LeaveWorkplace();
			}
		}
		m_GameTable->recalculate = false;
	}
}

void City::CalculateHappiness() {
	std::vector<Citizen*> to_remove;
	float totalHappiness = 0;
	m_serviceWorkers = 0;
	m_industrialWorkers = 0;

	for (auto& citizen : m_Citizens) {
		if (dynamic_cast<IndustrialArea*>(citizen->Get_Workplace())) {
			m_industrialWorkers++;
		}
		else if (dynamic_cast<ServiceArea*>(citizen->Get_Workplace())) {
			m_serviceWorkers++;
		}
	}

	float ratio = m_serviceWorkers * 1.f / m_industrialWorkers;
	int i = 0;
	for (auto& citizen : m_Citizens) {
		float happiness = 0;
		happiness += citizen->Calculate_Satisfaction();
		if (m_Money < 0) happiness -= 0.1;
		if (ratio < 0.5 || ratio > 2) happiness -= 0.1;
		if (happiness <= 0 && m_initialCitizens >= 50 && i>=49) { //első 50 lakos nem költözik el
			happiness = 0;
			to_remove.push_back(citizen);
		}
		totalHappiness += happiness;
		i++;
	}

	if (Get_CitizenSize() == 0) m_combinedHappiness = 0;
	else m_combinedHappiness = totalHappiness / (Get_CitizenSize() * 1.f);

	for (auto citizen : to_remove)
	{
		LeaveCity(citizen);
	}
}

void City::GenerateCitizens(unsigned int x)
{
	if (RoadNetwork::FindEmptyResidentialArea() == nullptr) return;
	

	for (unsigned int i = 0; i < x; i++)
	{
		Citizen* citizen = new Citizen();

		if (!JoinCity(citizen))
		{
			delete citizen;
		}
	}
}

void City::HandleLosingZone()
{
	std::vector<Citizen*> to_remove;

	for (auto citizen : m_Citizens)
	{
		if (citizen->Get_Residence() == nullptr)
		{
			citizen->LeaveWorkplace();

			Zone* residence = RoadNetwork::FindEmptyResidentialArea();
			Zone* workplace = RoadNetwork::FindEmptyWorkingArea(residence, m_serviceWorkers * 1.f / m_industrialWorkers);

			if (residence != nullptr)
			{
				citizen->JoinZone(residence);
				citizen->JoinZone(workplace);
			}
			else
			{
				//DO NOT CALL LEAVECITY HERE!!!
				to_remove.push_back(citizen);
			}
		}
		else if (citizen->Get_Workplace() == nullptr)
		{
			Zone* workplace = RoadNetwork::FindEmptyWorkingArea(citizen->Get_Residence(), m_serviceWorkers * 1.f / m_industrialWorkers);

			if (workplace != nullptr)
			{
				citizen->JoinZone(workplace);
			}
		}
	}

	for (auto citizen : to_remove)
	{
		LeaveCity(citizen);
	}
}

bool City::JoinCity(Citizen* citizen)
{
	if (citizen == nullptr) return false;

	Zone* residence = nullptr;
	if (m_initialCitizens < 50) {
		//a kezdetben 50 lakos feltétel nélkül beköltözik
		residence = RoadNetwork::FindEmptyResidentialArea();
		if (residence != nullptr) m_initialCitizens++;
	}
	else {
		//a kezdeti után csak akkor költözik be, ha talál elég jó lakózónát
		residence = RoadNetwork::FindOptimalResidentialArea(m_combinedHappiness);
	}

	Zone* workplace = RoadNetwork::FindEmptyWorkingArea(residence, m_serviceWorkers * 1.f / m_industrialWorkers);

	if (residence != nullptr)
	{
		m_Citizens.insert(citizen);
		citizen->JoinZone(residence);
		citizen->JoinZone(workplace);
		return true;
	}

	return false;
}

void City::LeaveCity(Citizen* citizen)
{
	if (citizen == nullptr) return;
	if (m_Citizens.find(citizen) == m_Citizens.end()) return;

	citizen->LeaveResidence();
	citizen->LeaveWorkplace();

	m_Citizens.erase(citizen);
	delete citizen;
}

void City::UpgradeField(int x, int y)
{
	if (m_GameTable->Get_TableValue(x, y)->IsZone())
	{
		Zone* zone = dynamic_cast<Zone*>(m_GameTable->Get_TableValue(x, y));

		if (zone->UpgradeZone())
		{
			float cost = zone->Get_BuildCost();
			UpdateMoney(-cost);
			MONEY_LOG << "- " << cost << "$ >> Upgrading zone {" << Get_TimeStr() << "}" << std::endl;
		}
	}
}

void City::SimulatePopulationAging() //should be called yearly
{
	std::vector<Citizen*> to_remove;

	for (auto citizen : m_Citizens)
	{
		citizen->Increase_Age();

		if (citizen->IsPensioner())
		{
			if (citizen->Get_Workplace() != nullptr)
			{
				citizen->LeaveWorkplace();
			}

			int yearsInPension = citizen->Get_Age() - 65;
			double probabilityOfRIP = (yearsInPension + 1) * 0.025;

			double random = (double)rand() / RAND_MAX;

			if (random < probabilityOfRIP)
			{
				to_remove.push_back(citizen);
			}
		}
	}

	for (auto citizen : to_remove)
	{
		LeaveCity(citizen);
		JoinCity(new Citizen());
	}
}

void City::GenerateForests(int iterations, double initialRatio)
{
	GenerateCellularFields(iterations, initialRatio, FieldType::FOREST);
}

void City::GenerateLakes(int iterations, double initialRatio)
{
	GenerateCellularFields(iterations, initialRatio, FieldType::LAKE);
}

void City::Set_TaxRate(FieldType type, float rate)
{
	switch (type)
	{
		case RESIDENTIAL_LVL1: ResidentalArea::SetLvl1TaxRate(rate); break;
		case RESIDENTIAL_LVL2: ResidentalArea::SetLvl2TaxRate(rate); break;
		case RESIDENTIAL_LVL3: ResidentalArea::SetLvl3TaxRate(rate); break;
		case INDUSTRIAL_LVL1: IndustrialArea::SetLvl1TaxRate(rate); break;
		case INDUSTRIAL_LVL2: IndustrialArea::SetLvl2TaxRate(rate); break;
		case INDUSTRIAL_LVL3: IndustrialArea::SetLvl3TaxRate(rate); break;
		case SERVICE_LVL1: ServiceArea::SetLvl1TaxRate(rate); break;
		case SERVICE_LVL2: ServiceArea::SetLvl2TaxRate(rate); break;
		case SERVICE_LVL3: ServiceArea::SetLvl3TaxRate(rate); break;
	}
}

void City::Set_GameTableValue(int x, int y, FieldType type, FieldDirection dir)
{ 
	GameField* PreviousField = m_GameTable->Get_TableValue(x, y);

	if (IsBuildable(type, dir, x, y))
	{
		if (type == STADIUM || type == POWERSTATION || type == UNIVERSITY)
		{
			m_GameTable->Set_TableValue(x, y, type, dir);
			m_GameTable->Set_TableValue(x + 1, y, m_GameTable->Get_TableValue(x, y));
			m_GameTable->Set_TableValue(x, y + 1, m_GameTable->Get_TableValue(x, y));
			m_GameTable->Set_TableValue(x + 1, y + 1, m_GameTable->Get_TableValue(x, y));
		}
		else if (type == HIGHSCHOOL)
		{
			m_GameTable->Set_TableValue(x, y, type, dir);
			if (dir == FRONT || dir == BACK)  m_GameTable->Set_TableValue(x, y + 1, m_GameTable->Get_TableValue(x, y));
			if (dir == RIGHT || dir == LEFT)  m_GameTable->Set_TableValue(x + 1, y, m_GameTable->Get_TableValue(x, y));
		}
		else
		{
			m_GameTable->Set_TableValue(x, y, type, dir);
		}

		UpdateMoney(-1 * GameField::CalculateBuildCost(type));

		BUILD_LOG << GameField::ConvertTypeToStr(type) << ": " << GameField::CalculateBuildCost(type) << "$" << std::endl;
	}

	GameField* CurrentField = m_GameTable->Get_TableValue(x, y);

	if (PreviousField != CurrentField
		&& (PreviousField->Get_Type() == RESIDENTIAL_LVL1 ||
			PreviousField->Get_Type() == RESIDENTIAL_LVL2 ||
			PreviousField->Get_Type() == RESIDENTIAL_LVL3))
	{
		--m_NumberOfResidences;
	}
	else if (PreviousField != CurrentField
		&& (CurrentField->Get_Type() == RESIDENTIAL_LVL1 ||
			CurrentField->Get_Type() == RESIDENTIAL_LVL2 ||
			CurrentField->Get_Type() == RESIDENTIAL_LVL3))
	{
		++m_NumberOfResidences;
	}
}

void City::GenerateCellularFields(int iterations, double initialRatio, FieldType fieldType)
{
	// simple cellular automata algorithm

	int tableSize = m_GameTable->Get_TableSize();
	std::vector<std::vector<bool>> cellularMatrix(tableSize, std::vector<bool>(tableSize, false));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	for (int x = 0; x < tableSize; ++x) {
		for (int y = 0; y < tableSize; ++y) {
			if (dis(gen) < initialRatio) {
				cellularMatrix[x][y] = true;
			}
		}
	}

	for (int i = 0; i < iterations; ++i) {
		std::vector<std::vector<bool>> newMatrix = cellularMatrix;
		for (int x = 0; x < tableSize; ++x) {
			for (int y = 0; y < tableSize; ++y) {
				int neighbors = 0;
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						int nx = x + dx;
						int ny = y + dy;
						if (nx >= 0 && nx < tableSize && ny >= 0 && ny < tableSize && !(dx == 0 && dy == 0)) {
							if (cellularMatrix[nx][ny]) {
								neighbors++;
							}
						}
					}
				}
				if (cellularMatrix[x][y]) {
					newMatrix[x][y] = neighbors >= 4;
				}
				else {
					newMatrix[x][y] = neighbors >= 5;
				}
			}
		}
		cellularMatrix = newMatrix;
	}

	for (int x = 0; x < tableSize; ++x) {
		for (int y = 0; y < tableSize; ++y) {
			if (cellularMatrix[x][y] && m_GameTable->Get_TableValue(x, y)->IsEmpty()) {
				m_GameTable->Set_TableValue(x, y, fieldType, FRONT);
			}
		}
	}
}

std::vector<std::vector<Point>> City::Get_CarPaths() const
{
	std::vector<std::vector<Point>> paths;
	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	for (int i = 0; i < m_GameTable->Get_TableSize(); ++i)
	{
		for (int j = 0; j < m_GameTable->Get_TableSize(); ++j)
		{
			Citizen* citizen = nullptr;

			if (Get_GameField(i, j)->IsZone())
				citizen = (dynamic_cast<Zone*>(Get_GameField(i, j))->GetRandomDriver());

			if (citizen != nullptr)
			{
				if (citizen->Get_Residence() != nullptr && citizen->Get_Workplace() != nullptr)
				{
					Point start = { 0,0 };

					for (int k = 0; k < 4; ++k)
					{
						if (dynamic_cast<Zone*>(Get_GameField(i, j))->IsResidentalArea())
						{
							if (citizen->Get_Residence()->Get_X() + dx[k] >= 0 && citizen->Get_Residence()->Get_X() + dx[k] < Get_GameTableSize()
								&& citizen->Get_Residence()->Get_Y() + dy[k] >= 0 && citizen->Get_Residence()->Get_Y() + dy[k] < Get_GameTableSize())
							{
								if (Get_GameField(citizen->Get_Residence()->Get_X() + dx[k], citizen->Get_Residence()->Get_Y() + dy[k])->IsRoad())
									start = { citizen->Get_Residence()->Get_X() + dx[k], citizen->Get_Residence()->Get_Y() + dy[k] };
							}
						}
						else
						{
							if (citizen->Get_Workplace()->Get_X() + dx[k] >= 0 && citizen->Get_Workplace()->Get_X() + dx[k] < Get_GameTableSize()
								&& citizen->Get_Workplace()->Get_Y() + dy[k] >= 0 && citizen->Get_Workplace()->Get_Y() + dy[k] < Get_GameTableSize())
							{
								if (Get_GameField(citizen->Get_Workplace()->Get_X() + dx[k], citizen->Get_Workplace()->Get_Y() + dy[k])->IsRoad())
									start = { citizen->Get_Workplace()->Get_X() + dx[k], citizen->Get_Workplace()->Get_Y() + dy[k] };
							}
						}
					}
					std::vector<Point> path;

					if (dynamic_cast<Zone*>(Get_GameField(i, j))->IsResidentalArea())
						path = m_GameTable->PathFinder(start, { citizen->Get_Workplace()->Get_X(), citizen->Get_Workplace()->Get_Y() });
					else
						path = m_GameTable->PathFinder(start, { citizen->Get_Residence()->Get_X(), citizen->Get_Residence()->Get_Y() });

					paths.push_back(path);
				}
			}
		}
	}
	return paths;
}
