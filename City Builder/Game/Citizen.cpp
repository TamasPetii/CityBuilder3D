#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"

void Citizen::JoinZone(Zone* zone)
{
	//Feltessz�k itt m�r biztosan tal�ltunk lak�helyet, de n�zz�k meg, hogy nem ugyan oda osztjuk-e be
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

	//TODO: �j lak�z�na / dolgoz�z�z�na keres�se, de ezt m�r a City kezelje le szerintem.
	//TODO: Ha nem tal�lt lak�z�n�t, akkor elhagyja a v�rost
}

float Citizen::Get_SatisfactionPoints() const
{
	return 0;
}

float Citizen::PayTax() const
{
	return 0;
}