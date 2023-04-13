#ifndef ZONE_H
#define ZONE_H

#include "../GameField.h"
#include <unordered_set>

class Citizen;

enum Level {
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

struct ZoneDetails {
public:
	int capacity;
	int contain;
	Level level;
};

class Zone : public GameField
{
protected: 
	Zone(Level level, FieldType type, int x, int y, float cost) : GameField(type, x, y, cost), level(level) {}
	Level level;
	ZoneDetails m_details;
	std::unordered_set<Citizen*> m_citizens;

public:
	~Zone() {}

	bool inline IsZone() const override { return true; }
	virtual inline bool IsResidentalArea() const { return false; }
	virtual inline bool IsWorkingArea() const { return false; }

	void JoinZone(Citizen* citizen);
	void LeaveZone(Citizen* citizen);
	void DeleteZone();

	Level Get_Level() { return this->level; }
	float Get_Satisfaction() const;
	float Set_Satisfaction(float value);
	float AddToSatisfaction(float value);
	virtual float GetTaxRate() const = 0;

	ZoneDetails inline Get_ZoneDetails() const { return m_details; }

private:

};

#endif
