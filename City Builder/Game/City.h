#pragma once

#include <unordered_set>
#include <sstream>

#include "GameTable.h"
#include "Citizen.h"
#include "RoadNetwork.h"


class City
{
public:
	City(int size, float money);
	~City() = default;

	void Simulate();
	void GenerateCitizens(unsigned int x);
	void HandleLooingZone();

	bool JoinCity(Citizen* citizen);
	void LeaveCity(Citizen* citizen);


	void DeleteField(int x, int y);
	void UpgradeField(int x, int y);
	void CollectTax();
	void CollectAnnualCosts();
	void UpdateMoney(float amount);
	void GenerateForests(int iterations, double initialRatio);
	void SimulatePopulationAging();

	void SetTaxRate(FieldType type, float rate);
	ZoneDetails Get_ZoneDetails(int x, int y) const;
	inline GameField* Get_GameField(int x, int y) const { return m_GameTable->Get_TableValue(x, y); };
	inline int Get_GameTableSize() const { return m_GameTable->Get_TableSize(); }
	void Set_GameTableValue(int x, int y, FieldType type);
	inline float Get_Money() { return m_Money; }

	static std::stringstream& Build_Log() { return m_BuildLog; }
	static std::stringstream& Money_Log() { return m_MoneyLog; }
	static bool& Log_Changed() { return m_ChangedLog; }
private:
	std::unordered_set<Citizen*> m_Citizens;
	GameTable* m_GameTable;

	float m_Money;
	float m_Tax = 0;


	static bool m_ChangedLog;
	static std::stringstream m_BuildLog;
	static std::stringstream m_MoneyLog;
	int m_MonthlyTickCounter = 0;
	int m_YearlyTickCounter = 0;
};
