#pragma once

#include <unordered_set>

#include "GameTable.h"
#include "Citizen.h"

class City
{
public:
	City(int size);
	~City() = default;

	void JoinCity(Citizen* citizen);
	void LeaveCity(Citizen* citizen);

	void DeleteField(int x, int y);
	void UpgradeField(int x, int y);
	void CollectTax();
	ZoneDetails Get_ZoneDetails(int x, int y) const;

	inline GameField* Get_GameField(int x, int y) const { return m_GameTable->Get_TableValue(x, y); };
	inline int Get_GameTableSize() const { return m_GameTable->Get_TableSize(); }
	inline void Set_GameTableValue(int x, int y, FieldType type) { m_GameTable->Set_TableValue(x, y, type); }
private:
	std::unordered_set<Citizen*> m_Citizens;
	GameTable* m_GameTable;

	float m_Money = 0;
	float m_Tax = 0;
};
