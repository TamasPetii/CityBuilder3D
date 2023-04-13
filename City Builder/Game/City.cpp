#include "City.h"

City::City(int size)
{
	m_GameTable = new GameTable(size);
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

ZoneDetails City::Get_ZoneDetails(int x, int y) const
{
	ZoneDetails z;
	return z;
}
