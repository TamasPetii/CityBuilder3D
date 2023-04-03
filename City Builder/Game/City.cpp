#include "City.h"

void City::JoinCity(Citizen* citizen)
{
	
}

void City::LeaveCity(Citizen* citizen)
{
	
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
	for (const Citizen& citizen : m_Citizens) {
		m_Money += citizen.PayTax();
	}
}

ZoneDetails City::Get_ZoneDetails(int x, int y) const
{

}
