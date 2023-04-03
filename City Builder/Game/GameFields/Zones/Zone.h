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

class ZoneDetails {
public:
	int capacity;
	int contain;
	Level level;
};

class Zone : public GameField
{
protected: 
	Zone(Level level) : GameField(), level(level) {}
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

	ZoneDetails inline Get_ZoneDetails() const { return m_details; }

private:
	Level level;
	ZoneDetails m_details;
	std::unordered_set<Citizen*> m_citizens;
};

#endif
