#ifndef ZONE_H
#define ZONE_H

#include "../GameField.h"
#include "../../Citizen.h"
#include <unordered_set>
#include <sstream>
#include <random>

enum Level
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

enum ZoneType
{
	RESIDENTIAL,
	INDUSTRIAL,
	SERVICE
};

class Zone : public GameField
{

public:
	Zone(Level level, FieldType type, FieldDirection direction, int x, int y);
	~Zone() {}

	//Identification Methodes
	inline bool IsZone() const override { return true; }
	inline virtual bool IsResidentalArea() const { return false; }
	inline virtual bool IsWorkingArea() const { return false; }
	inline bool IsThereEmptySpace() const { return m_Contain < m_Capacity ? true : false; }

	//Simulation Methodes
	void JoinZone(Citizen* citizen);
	void LeaveZone(Citizen* citizen);
	void DeleteZone();
	bool UpgradeZone();
	static bool CHANGED;

	//Getter Methodes
	inline int Get_Capacity() const { return m_Capacity; }
	inline int Get_Contain() const { return m_Contain; }
	inline float Get_Satisfaction() const { return m_Satisfaction; }
	inline float Get_Safety() const { return m_Safety; }
	inline float Get_IndustrialPenalty() const { return m_IndustrialPenalty; }
	inline Level Get_Level() const { return m_Level; }
	inline std::unordered_set<Citizen*>& Get_Citizens() { return m_citizens; }

	//Setter Methodes
	inline void Set_Capacity(int Capacity) { m_Capacity = Capacity; }
	inline void Set_Contain(int Contain) { m_Contain = Contain; }
	inline void Set_Satisfaction(float Satisfaction) { m_Satisfaction = Satisfaction; }
	inline void Set_Safety(float Safety) { m_Safety = Safety; }
	inline void Set_IndustrialPenalty(float IndustrialPenalty) { m_IndustrialPenalty = IndustrialPenalty; }
	inline void Set_Level(Level Level) { m_Level = Level; }
	float Get_ForestSatisfaction() { return m_details.forest_satisfaction; }
	void Add_ForestSatisfaction(float f) { m_details.forest_satisfaction += f; }
	void Set_ForestSatisfaction(float f) { m_details.forest_satisfaction = f; }

	//Add Methodes
	inline void Add_Satisfaction(float Satisfaction) { m_Satisfaction += Satisfaction; }
	inline void Add_Safety(float Safety) { m_Safety += Safety; }
	inline void Add_IndustrialPenalty(float IndustrialPenalty) { m_IndustrialPenalty += IndustrialPenalty; }

	//Other Methodes
	virtual float Calculate_TaxRate() const = 0;
	virtual float Calculate_TaxRatePercentage() const = 0;
	virtual float Calculate_NormalSatisfaction() const = 0;
	float Calculate_RealSatisfaction() const;
	float Calculate_RawSatisfaction() const;
	void AdjustCapacity();
	Citizen* GetRandomDriver();

	static std::string ToString(Zone* zone);

protected: 
	std::unordered_set<Citizen*> m_citizens;

	int m_Capacity;
	int m_Contain;
	float m_Satisfaction;
	float m_Safety;
	float m_IndustrialPenalty;
	Level m_Level;
};

#endif
