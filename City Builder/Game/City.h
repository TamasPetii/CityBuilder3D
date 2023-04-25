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

	float CalculateMonthlyTax();
	void CollectMonthlyTax();
	void CollectAnnualCosts();


	void UpdateMoney(float amount);
	void GenerateForests(int iterations, double initialRatio);
	void SimulatePopulationAging();

	void SetTaxRate(FieldType type, float rate);
	inline GameField* Get_GameField(int x, int y) const { return m_GameTable->Get_TableValue(x, y); };
	inline int Get_GameTableSize() const { return m_GameTable->Get_TableSize(); }
	void Set_GameTableValue(int x, int y, FieldType type, FieldDirection dir);
	inline float Get_Money() { return m_Money; }
	inline int Get_Time() { return m_DailyTickCounter; }
	inline std::string Get_Time_Str() { return std::to_string(Get_Year()) + "." + std::to_string(Get_Month()) + "." + std::to_string(Get_Day()); }

	static std::stringstream& Build_Log() { return m_BuildLog; }
	static std::stringstream& Money_Log() { return m_MoneyLog; }
	static bool& Log_Changed() { return m_ChangedLog; }

	int Get_Year() { return m_DailyTickCounter / 360 + 2000; }
	int Get_Month() { return m_DailyTickCounter % 360 / 30; }
	int Get_Day() { return (m_DailyTickCounter % 360) % 30 + 1; }

	int Get_CitizenSize() { return m_Citizens.size(); }
private:
	std::unordered_set<Citizen*> m_Citizens;
	GameTable* m_GameTable;

	float m_Money;
	float m_Tax = 0;


	static bool m_ChangedLog;
	static std::stringstream m_BuildLog;
	static std::stringstream m_MoneyLog;
	int m_DailyTickCounter = 0;
};
