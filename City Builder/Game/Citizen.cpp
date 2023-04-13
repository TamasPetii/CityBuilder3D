#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include <iostream>

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
		std::cout << this << " joined residential zone: " << zone << std::endl;
		m_Residence = zone;
	}
	if (zone->IsWorkingArea())
	{
		std::cout << this << " joined working zone: " << zone << std::endl;
		m_Workplace = zone;
	}
}

void Citizen::LeaveResidence()
{
	if (m_Residence == nullptr) return;

	std::cout << this << " left residential zone: " << m_Residence << std::endl;

	m_Residence->LeaveZone(this);
	m_Residence = nullptr;
}

void Citizen::LeaveWorkplace()
{
	if (m_Workplace == nullptr) return;

	std::cout << this << " left workplace zone: " << m_Workplace << std::endl;

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
		std::cout << this << " left deleted zone: " << m_Residence << std::endl;
		m_Residence = nullptr;
	}

	if (zone->IsWorkingArea())
	{
		std::cout << this << " left deleted zone: " << m_Workplace << std::endl;
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