#include "City.h"

City::City(int size)
{
	m_GameTable = new GameTable(size);
}

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
	for (const Citizen* citizen : m_Citizens) {
		m_Money += citizen->PayTax();
	}
}

ZoneDetails City::Get_ZoneDetails(int x, int y) const
{
	ZoneDetails z;
	z.capacity = 0;
	return z;
}
