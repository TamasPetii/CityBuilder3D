#pragma once

#include "GameTable.h"
#include "Citizen.h"
#include "Zone.h"

#include <unordered_set>

class City
{
public:
	City(float initialMoney, float initialTax) : m_Money(initialMoney), m_Tax(initialTax) {}
	~City() = default;

	void JoinCity(Citizen* citizen);
	void LeaveCity(Citizen* citizen);
	void DeleteField(int x, int y);
	void UpgradeField(int x, int y);
	void CollectTax();
	ZoneDetails Get_ZoneDetails(int x, int y) const;

private:
	GameTable* m_GameTable;
	std::unordered_set<Citizen> m_Citizens;
	float m_Money;
	float m_Tax;
};
