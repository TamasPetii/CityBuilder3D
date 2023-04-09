#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"

void Citizen::JoinZone(Zone* zone)
{
	if (zone->IsThereEmptySpace())
	{
		zone->IsResidentalArea() ? m_Residence = zone : m_Workplace = zone;
		zone->JoinZone(this);
	}
	if (m_Workplace == nullptr)
	{
		//TODO: check for workplace
	}
	if (m_Residence == nullptr)
	{
		//TODO: check for home
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
	zone->IsResidentalArea() ? LeaveResidence() : LeaveWorkplace();
	JoinZone(zone);
}

void Citizen::DeletedZone(Zone* zone)
{
	zone->IsResidentalArea() ? m_Residence = nullptr : m_Workplace = nullptr;

	if (m_Workplace == nullptr)
	{
		//TODO: check for workplace
	}
	if (m_Residence == nullptr)
	{
		//TODO: check for home
	}
	if (m_Workplace == nullptr) //Ha nem talált új otthont, akkor ehagyja a várost
	{
		//TODO: leave the city
	}
}

float Citizen::Get_SatisfactionPoints() const
{
	return 0;
}

float Citizen::PayTax() const
{
	return 0;
}