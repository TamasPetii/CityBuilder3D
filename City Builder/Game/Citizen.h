#pragma once

#include "Zone.h"

class Citizen
{
public:
	Citizen() {}
	~Citizen() {}

	void JoinZone(Zone* zone);
	void LeaveZone(Zone* zone);
	void ChangeZone(Zone* zone);
	void DeleteZone(Zone* zone);
	float Get_SatisfactionPoints() const;
	float PayTax() const;

private:
	Zone* m_Residence;
	Zone* m_Workplace;
	int m_Age;
};
