#pragma once

#include <unordered_set>
#include <sstream>

#include "GameTable.h"
#include "Citizen.h"
#include "RoadNetwork.h"


class City
{
public:
	City(int size);
	City(int size, int money, int time);
	~City() = default;

	//Static Methodes / Members
	static std::stringstream BUILD_LOG;
	static std::stringstream MONEY_LOG;

	//Simulation Methodes
	void Simulate();
	bool JoinCity(Citizen* citizen);
	void LeaveCity(Citizen* citizen);
	void HandleLosingZone();
	void GenerateCitizens(unsigned int x);

	//Getter Methodes
	inline int Get_Money() const { return m_Money; }
	inline int Get_Year() const  { return m_DailyTickCounter / 360 + 2000; }
	inline int Get_Month() const { return m_DailyTickCounter % 360 / 30 + 1; }
	inline int Get_Day() const { return (m_DailyTickCounter % 360) % 30 + 1; }
	inline int Get_Time() const { return m_DailyTickCounter; }
	inline int Get_GameTableSize() const { return m_GameTable->Get_TableSize(); }
	inline int Get_CitizenSize() { return m_Citizens.size(); }
	inline std::unordered_set<Citizen*>& Get_Citizens() { return m_Citizens; }
	inline int Get_NumberOfResidences() const { return m_NumberOfResidences; }
	inline float Get_CombinedHappiness() { return Get_CitizenSize() == 0 ? 0 : m_combinedHappiness * 100; }
	std::string Get_TimeStr() const;
	GameField* Get_GameField(int x, int y) const;
	std::vector<std::vector<Point>> Get_CarPaths() const;

	//Setter Methodes
	void Set_TaxRate(FieldType type, float rate);
	void Set_GameTableValue(int x, int y, FieldType type, FieldDirection dir);

	void UpgradeField(int x, int y);
	bool IsBuildable(FieldType type, FieldDirection dir, int x, int y) { return m_GameTable->IsBuildable(type, dir, x, y) || type == EMPTY || type == CRATER; }

	std::vector<Point> Get_FireTruckPath(int startX, int startY) const;
	GameTable* Get_GameTable() { return m_GameTable; }
	bool Validate(int c1, int c2) { return m_GameTable->ValidateCoordinate(c1, c2); }

protected:
	void GenerateCellularFields(int iterations, double initialRatio, FieldType fieldType);
	void GenerateForests(int iterations, double initialRatio);
	void GenerateLakes(int iterations, double initialRatio);
	float CalculateMonthlyTax();
	void  CollectMonthlyTax();
	void  CollectAnnualCosts();
	void  UpdateMoney(float amount);
	void SimulatePopulationAging();
	void SimulateForestAging();
	void CalculateHappiness();
	void CalculateForestSatisfaction(int radius);
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
	GameTable* m_GameTable;
	std::unordered_set<Citizen*> m_Citizens;
	std::vector<std::pair<int, int>> BresenhamAlgorithm(int x0, int y0, int x1, int y1);

	float m_Money = 0;
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
