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
	void GenerateLakes(int iterations, double initialRatio);
	void GenerateGraduatedCitizens(int randomCitizenCount);
	void SimulatePopulationAging();
	void CalculateHappiness();
	void HandleRecalculation();

	void SetTaxRate(FieldType type, float rate);
	inline GameField* Get_GameField(int x, int y) const { return m_GameTable->Get_TableValue(x, y); };
	inline int Get_GameTableSize() const { return m_GameTable->Get_TableSize(); }
	bool IsBuildable(FieldType type, FieldDirection dir, int x, int y) { return m_GameTable->IsBuildable(type, dir, x, y) || type == EMPTY || type == CRATER; }
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
	std::vector<std::vector<Point>> Get_CarPaths() const;
	int Get_CitizenSize() { return m_Citizens.size(); }
	inline int Get_NumberOfResidences() const { return m_NumberOfResidences; }

	float Get_CombinedHappiness() { if (Get_CitizenSize() == 0) return 0; else return m_combinedHappiness * 100; }

private:
	void GenerateCellularFields(int iterations, double initialRatio, FieldType fieldType);

	std::unordered_set<Citizen*> m_Citizens;
	GameTable* m_GameTable;

	float m_Money;
	float m_Tax = 0;

	static bool m_ChangedLog;
	static std::stringstream m_BuildLog;
	static std::stringstream m_MoneyLog;
	int m_DailyTickCounter = 0;

	float m_combinedHappiness = 0;
	int m_serviceWorkers = 0;
	int m_industrialWorkers = 0;

	int m_initialCitizens = 0;
	int m_NumberOfResidences = 0;
	int m_citizensWithIntermediateEducation = 0;
	int m_citizensWithAdvancedEducation = 0;
	int m_maxCitizensWithIntermediateEducation = 200;
	int m_maxCitizensWithAdvancedEducation = 200;
};
