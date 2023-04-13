#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"

void Citizen::JoinZone(Zone* zone)
{
	//Feltesszük itt már biztosan találtunk lakóhelyet, de nézzük meg, hogy nem ugyan oda osztjuk-e be
	if (zone == m_Residence || zone == m_Workplace) return;

	zone->JoinZone(this);

	if (zone->IsResidentalArea())
	{
		m_Residence = zone;
	}
	if (zone->IsWorkingArea())
	{
		m_Workplace = zone;
	}
}

void Citizen::LeaveResidence()
{
	m_Residence->LeaveZone(this);
	m_Residence = nullptr;
}

void Citizen::LeaveWorkplace()
{
	m_Workplace->LeaveZone(this);
	m_Workplace = nullptr;
}

void Citizen::ChangeZone(Zone* zone)
{
	if (zone->IsResidentalArea())
	{
		LeaveResidence();
	}
	if (zone->IsWorkingArea()) 
	{
		LeaveWorkplace();
	}

	JoinZone(zone);
}

void Citizen::DeletedZone(Zone* zone)
{
	if (zone->IsResidentalArea())
	{
		m_Residence = nullptr;
	}

	if (zone->IsWorkingArea())
	{
		m_Workplace = nullptr;
	}

	//TODO: Új lakózóna / dolgozózózóna keresése, de ezt már a City kezelje le szerintem.
	//TODO: Ha nem talált lakózónát, akkor elhagyja a várost
}

float Citizen::Get_SatisfactionPoints() const
{
	return 0;
}

float Citizen::PayTax() const
{
	return 0;
}