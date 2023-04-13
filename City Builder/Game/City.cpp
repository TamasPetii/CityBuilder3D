#include "City.h"

#include <random>

City::City(int size, float money): m_Money(money)
{
	m_GameTable = new GameTable(size);

	GenerateForests(5, 0.4);
}

void City::JoinCity(Citizen* citizen)
{
	if (citizen == nullptr) return;

	//Itt hátározzuk meg, hogy melyik zónába kerüljün. NetWork keres neki egyet.
	//Ha nincs zóna vagy nincs olyan ahol lenne férőhely, akkor legyen nullptr így jelezve azt hogy nem tudjuk beosztani sehová
	Zone* residence = nullptr;

	if (residence != nullptr)
	{
		m_Citizens.insert(citizen);
		citizen->JoinZone(dynamic_cast<Zone*>(residence));
	}
}

void City::LeaveCity(Citizen* citizen)
{
	if (citizen == nullptr) return; // Nem létezõ polgárt adunk meg
	if (m_Citizens.find(citizen) == m_Citizens.end()) return; //Nem található meg a polgárok között

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

ZoneDetails City::Get_ZoneDetails(int x, int y) const
{
	ZoneDetails z;
	z.capacity = 0;
	return z;
}