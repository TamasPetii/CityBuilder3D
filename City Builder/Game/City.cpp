#include "City.h"

City::City(int size)
{
	m_GameTable = new GameTable(size);
}

void City::JoinCity(Citizen* citizen)
{
	if (citizen == nullptr) return;

	GameField* mostLiveableResidentalArea = CheckForHome();

	//TODO: A mostLiveableResidentalArea elégedettségi szintje alapján és a város átlagos elégedettsége szerint számolni egy valószínûséget. Ezen valószínûséggel kerül beosztásra a zónába.

	if (mostLiveableResidentalArea != nullptr)
	{
		m_Citizens.insert(citizen);
		citizen->JoinZone(dynamic_cast<Zone*>(mostLiveableResidentalArea));
	}
}

// othon keresése, maximum kiválasztást végzünk az összes lakóhelyen az elégedettségük alapján és a legnagyobb elégedettséggel és szabad hellyel rendelkezõ lakózónát kapjuk vissza
// ez a zóna lesz a polgár kiszemelt zónája
// ha nagy a zóna elégedettsége akkor nagyobb valószínûséggel költözik a városba, ha kicsi, akkor kisebb valószínûséggel (ez a JoinCity-ben történik eldöntésre)
// ha nullpointer a visszatérés, akkor nincs szabad lakóhely
// (feladat szöveg szerint a cél lakózónánánl csak a közeli munkahely és és ipari terület befolyásolja a polgárok érkezését, de talán nem baj, ha a teljes elégedettséget nézzük)
GameField* City::CheckForHome() 
{
	GameField* mostLiveableResidentalArea = nullptr;

	for (int i = 0; i < m_GameTable->Get_TableSize(); ++i)
	{
		for (int j = 0; j < m_GameTable->Get_TableSize(); ++j)
		{
			GameField* currentGameField = m_GameTable->Get_TableValue(i, j);
			if (currentGameField->IsZone())
			{
				if (dynamic_cast<Zone*>(currentGameField)->IsResidentalArea() && dynamic_cast<Zone*>(currentGameField)->IsThereEmptySpace())
				{
					if (mostLiveableResidentalArea == nullptr)
					{
						mostLiveableResidentalArea = currentGameField;
					}
					else if (mostLiveableResidentalArea->Get_SatisfactionPoints() < currentGameField->Get_SatisfactionPoints())
					{
						mostLiveableResidentalArea = currentGameField;
					}
				}
			}
		}
	}
	
	return mostLiveableResidentalArea;
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
