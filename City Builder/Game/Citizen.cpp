#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include <iostream>

std::stringstream Citizen::log;
bool Citizen::log_changed = false;

Citizen::Citizen()
{
	m_Education = BASIC;
	m_Age = 18;
}

void Citizen::JoinZone(Zone* zone)
{
	if (zone == m_Residence || zone == m_Workplace) return;

	zone->JoinZone(this);

	if (zone->IsResidentalArea())
	{
		log << this << " joined residential zone: " << zone << std::endl;
		log_changed = true;
		m_Residence = zone;
	}
	if (zone->IsWorkingArea())
	{
		log << this << " joined working zone: " << zone << std::endl;
		log_changed = true;
		m_Workplace = zone;
	}
}

void Citizen::LeaveResidence()
{
	if (m_Residence == nullptr) return;

	log << this << " left residential zone: " << m_Residence << std::endl;
	log_changed = true;

	m_Residence->LeaveZone(this);
	m_Residence = nullptr;
}

void Citizen::LeaveWorkplace()
{
	if (m_Workplace == nullptr) return;

	log << this << " left workplace zone: " << m_Workplace << std::endl;
	log_changed = true;

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
		log << this << " left deleted zone: " << m_Residence << std::endl;
		log_changed = true;
		m_Residence = nullptr;
	}

	if (zone->IsWorkingArea())
	{
		log << this << " left deleted zone: " << m_Workplace << std::endl;
		log_changed = true;
		m_Workplace = nullptr;
	}
}

float Citizen::Get_SatisfactionPoints() const
{
	return 0;
}

float Citizen::PayTax() const
{
	float educationRate = m_Education == BASIC ? 1.2 : (m_Education == INTERMEDIATE ? 1.5 : 2.0);

	if (IsPensioner())
		return -100; //TODO: Calculate pension
	else
		return (m_Workplace->GetTaxRate() + m_Residence->GetTaxRate()) * educationRate;
}