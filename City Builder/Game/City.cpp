#include "City.h"
#include <stdlib.h> 
#include <time.h>

City::City(int size, float money): m_Money(money)
{
	m_GameTable = new GameTable(size);
}

void City::Simulate()
{
	GenerateCitizens(rand() % 2 == 0 ? rand() % 2 : 0);
	HandleLooingZone();
}

void City::GenerateCitizens(unsigned int x)
{
	if (RoadNetwork::FindEmptyResidentialArea() == nullptr) return;

	for (int i = 0; i < x; i++)
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

void City::CollectTax()
{
	for (const Citizen* citizen : m_Citizens) {
		m_Money += citizen->PayTax();
	}
}

void City::CollectAnnualCosts()
{
	float totalCost = m_GameTable->Get_TotalCost();
	UpdateMoney(-totalCost);
}

void City::UpdateMoney(float amount)
{
	m_Money += amount;
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

ZoneDetails City::Get_ZoneDetails(int x, int y) const
{
	ZoneDetails z;
	z.capacity = 0;
	return z;
}
