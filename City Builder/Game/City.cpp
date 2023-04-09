#include "City.h"

City::City(int size)
{
	m_GameTable = new GameTable(size);
}

void City::JoinCity(Citizen* citizen)
{
	if (citizen == nullptr) return;

	GameField* mostLiveableResidentalArea = CheckForHome();

	//TODO: A mostLiveableResidentalArea el�gedetts�gi szintje alapj�n �s a v�ros �tlagos el�gedetts�ge szerint sz�molni egy val�sz�n�s�get. Ezen val�sz�n�s�ggel ker�l beoszt�sra a z�n�ba.

	if (mostLiveableResidentalArea != nullptr)
	{
		m_Citizens.insert(citizen);
		citizen->JoinZone(dynamic_cast<Zone*>(mostLiveableResidentalArea));
	}
}

// othon keres�se, maximum kiv�laszt�st v�gz�nk az �sszes lak�helyen az el�gedetts�g�k alapj�n �s a legnagyobb el�gedetts�ggel �s szabad hellyel rendelkez� lak�z�n�t kapjuk vissza
// ez a z�na lesz a polg�r kiszemelt z�n�ja
// ha nagy a z�na el�gedetts�ge akkor nagyobb val�sz�n�s�ggel k�lt�zik a v�rosba, ha kicsi, akkor kisebb val�sz�n�s�ggel (ez a JoinCity-ben t�rt�nik eld�nt�sre)
// ha nullpointer a visszat�r�s, akkor nincs szabad lak�hely
// (feladat sz�veg szerint a c�l lak�z�n�n�nl csak a k�zeli munkahely �s �s ipari ter�let befoly�solja a polg�rok �rkez�s�t, de tal�n nem baj, ha a teljes el�gedetts�get n�zz�k)
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
	if (citizen == nullptr) return; // Nem l�tez� polg�rt adunk meg
	if (m_Citizens.find(citizen) == m_Citizens.end()) return; //Nem tal�lhat� meg a polg�rok k�z�tt

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
