#include "City.h"
#include <stdlib.h> 
#include <time.h>
#include <random>

bool City::m_ChangedLog = false;
std::stringstream City::m_BuildLog;
std::stringstream City::m_MoneyLog;

City::City(int size, float money): m_Money(money)
{
	m_GameTable = new GameTable(size);

	GenerateForests(5, 0.4);
}

void City::Simulate()
{
	GenerateCitizens(rand() % 2 == 0 ? rand() % 2 : 0);
	HandleLooingZone();

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
	
	m_MoneyLog << ((tax >= 0) ? "+ " : "- ") << tax << "$ >> Monthly Tax {" << Get_Time_Str() << "}" << std::endl;
	m_ChangedLog = true;

}

void City::CollectAnnualCosts()
{
	float cost = m_GameTable->Get_TotalCost();
	UpdateMoney(-cost);

	m_MoneyLog << "- " << cost << "$ >> Annual Cost {" << Get_Time_Str() << "}" << std::endl;
	m_ChangedLog = true;
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

void City::HandleLooingZone()
{
	std::vector<Citizen*> to_remove;

	for (auto citizen : m_Citizens)
	{
		if (citizen->Get_Residence() == nullptr)
		{
			citizen->LeaveWorkplace();

			Zone* residence = RoadNetwork::FindEmptyResidentialArea();
			Zone* workplace = RoadNetwork::FindEmptyWorkingArea(residence);

			if (residence != nullptr)
			{
				citizen->JoinZone(residence);
				citizen->JoinZone(workplace);
			}
			else
			{
				//DO NOT CALL LEAVECITY HERE!!! It will delete citizen from unodered_set. And you will get error bc we are looping on it
				to_remove.push_back(citizen);
			}
		}
		else if (citizen->Get_Workplace() == nullptr)
		{
			Zone* workplace = RoadNetwork::FindEmptyWorkingArea(citizen->Get_Residence());

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

	Zone* residence = RoadNetwork::FindEmptyResidentialArea();
	Zone* workplace = RoadNetwork::FindEmptyWorkingArea(residence);

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

void City::DeleteField(int x, int y)
{

}

void City::UpgradeField(int x, int y)
{
	m_GameTable->UpgradeField(x, y);
}

void City::SimulatePopulationAging() //should be called yearly
{
	std::vector<Citizen*> to_remove;

	for (auto citizen : m_Citizens)
	{
		citizen->Age();

		if (citizen->IsPensioner())
		{
			if (citizen->Get_Workplace() != nullptr)
			{
				//std::cout << "A retired from work!" << std::endl;
				citizen->LeaveWorkplace();
			}

			int yearsInPension = citizen->Get_Age() - 65;
			double probabilityOfRIP = (yearsInPension + 1) * 0.025;

			double random = (double)rand() / RAND_MAX;

			if (random < probabilityOfRIP)
			{
				//std::cout << "A citizen died at the age of: " << citizen->Get_Age() << std::endl;
				to_remove.push_back(citizen);
			}
		}
	}

	for (auto citizen : to_remove)
	{
		LeaveCity(citizen);
		JoinCity(new Citizen(18));
	}
}

void City::GenerateForests(int iterations, double initialRatio)
{
	// simple cellular automata algorithm

	int tableSize = m_GameTable->Get_TableSize();
	std::vector<std::vector<bool>> forestMatrix(tableSize, std::vector<bool>(tableSize, false));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	for (int x = 0; x < tableSize; ++x) {
		for (int y = 0; y < tableSize; ++y) {
			if (dis(gen) < initialRatio) {
				forestMatrix[x][y] = true;
			}
		}
	}

	for (int i = 0; i < iterations; ++i) {
		std::vector<std::vector<bool>> newMatrix = forestMatrix;
		for (int x = 0; x < tableSize; ++x) {
			for (int y = 0; y < tableSize; ++y) {
				int neighbors = 0;
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						int nx = x + dx;
						int ny = y + dy;
						if (nx >= 0 && nx < tableSize && ny >= 0 && ny < tableSize && !(dx == 0 && dy == 0)) {
							if (forestMatrix[nx][ny]) {
								neighbors++;
							}
						}
					}
				}
				if (forestMatrix[x][y]) {
					newMatrix[x][y] = neighbors >= 4;
				}
				else {
					newMatrix[x][y] = neighbors >= 5;
				}
			}
		}
		forestMatrix = newMatrix;
	}

	for (int x = 0; x < tableSize; ++x) {
		for (int y = 0; y < tableSize; ++y) {
			if (forestMatrix[x][y]) {
				m_GameTable->Set_TableValue(x, y, FieldType::FOREST);
			}
		}
	}
}

void City::SetTaxRate(FieldType type, float rate)
{
	switch (type)
	{
		case RESIDENTIAL_LVL1: ResidentalArea::SetLvl1TaxRate(rate);
		case RESIDENTIAL_LVL2: ResidentalArea::SetLvl2TaxRate(rate);
		case RESIDENTIAL_LVL3: ResidentalArea::SetLvl3TaxRate(rate);
		case INDUSTRIAL_LVL1: IndustrialArea::SetLvl1TaxRate(rate);
		case INDUSTRIAL_LVL2: IndustrialArea::SetLvl2TaxRate(rate);
		case INDUSTRIAL_LVL3: IndustrialArea::SetLvl3TaxRate(rate);
		case SERVICE_LVL1: ServiceArea::SetLvl1TaxRate(rate);
		case SERVICE_LVL2: ServiceArea::SetLvl2TaxRate(rate);
		case SERVICE_LVL3: ServiceArea::SetLvl3TaxRate(rate);
	}
}

void City::Set_GameTableValue(int x, int y, FieldType type, FieldDirection dir)
{ 
	GameField* PreviousField = m_GameTable->Get_TableValue(x, y);
	m_GameTable->Set_TableValue(x, y, type);
	GameField* CurrentField = m_GameTable->Get_TableValue(x, y);
	if (PreviousField != CurrentField)
	{
		CurrentField->Set_FieldDirection(dir);
    	m_BuildLog << GameField::ConvertTypeToStr(type) << ": " << CurrentField->Get_Cost() << "$" << std::endl;
		m_ChangedLog = true;
	}
}

std::vector<std::vector<Point>> City::Get_CarPaths()
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
			{
				if ((dynamic_cast<Zone*>(Get_GameField(i, j)))->IsResidentalArea())
				{
					citizen = (dynamic_cast<ResidentalArea*>(Get_GameField(i, j))->GetRandomDriver());
				}
			}

			if (citizen != nullptr)
			{
				if (citizen->Get_Residence() != nullptr && citizen->Get_Workplace() != nullptr)
				{
					Point start = { 0,0 };

					for (int k = 0; k < 4; ++k)
					{
						if (citizen->Get_Residence()->Get_X() + dx[k] >= 0 && citizen->Get_Residence()->Get_X() + dx[k] < Get_GameTableSize()
							&& citizen->Get_Residence()->Get_Y() + dy[k] >= 0 && citizen->Get_Residence()->Get_Y() + dy[k] < Get_GameTableSize())
						{
							if (Get_GameField(citizen->Get_Residence()->Get_X() + dx[k], citizen->Get_Residence()->Get_Y() + dy[k])->IsRoad())
								start = { citizen->Get_Residence()->Get_X() + dx[k], citizen->Get_Residence()->Get_Y() + dy[k] };
						}
					}
					std::vector<Point> path = m_GameTable->PathFinder(start, { citizen->Get_Workplace()->Get_X(), citizen->Get_Workplace()->Get_Y() });
					paths.push_back(path);
				}
			}
		}
	}
	return paths;
}