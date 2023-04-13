#include "City.h"

City::City(int size, float money): m_Money(money)
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
