#ifndef ZONE_H
#define ZONE_H

#include "../GameField.h"
#include "../../Citizen.h"
#include <unordered_set>
#include <sstream>

enum Level {
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

struct ZoneDetails {
public:
	int capacity;
	int contain;
	float satisfaction;
	float safety;
	float industrial_penalty;
	Level level;
};

class Zone : public GameField
{
protected: 
	Zone(Level level, FieldType type, int x, int y, float cost);

	ZoneDetails m_details;
	std::unordered_set<Citizen*> m_citizens;

public:
	~Zone() {}

	bool inline IsZone() const override { return true; }
	virtual inline bool IsResidentalArea() const { return false; }
	virtual inline bool IsWorkingArea() const { return false; }
	inline bool IsThereEmptySpace() const { return m_details.contain < m_details.capacity ? true : false; }

	void JoinZone(Citizen* citizen);
	void LeaveZone(Citizen* citizen);
	void DeleteZone();

	Level Get_Level() { return m_details.level; }
	float Get_Satisfaction() const;
	float Get_SatisfactionAll() const;
	void Add_Satisfaction(float f) { m_details.satisfaction += f; }
	void Set_Satisfaction(float f) { m_details.satisfaction = f; }
	void Add_Safety(float f) { m_details.safety += f; }
	void Set_Safety(float f) { m_details.safety = f; }
	void Add_IndustrialPenalty(float f) { m_details.industrial_penalty += f; }
	void Set_IndustrialPenalty(float f) { m_details.industrial_penalty = f; }
	virtual float GetTaxRate() const = 0;

	inline ZoneDetails Get_ZoneDetails() const { return m_details; }

	std::string Get_CitizenDetails();
};

#endif
