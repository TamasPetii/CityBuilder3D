#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include <iostream>

std::stringstream Citizen::log;
bool Citizen::log_changed = false;

Citizen::Citizen()
{
	m_Education = BASIC;

	int minAge = 18;
	int maxAge = 60;

	int range = maxAge - minAge + 1;

	m_Age = rand() % range + minAge;
}

Citizen::Citizen(int age)
{
	m_Education = BASIC;
	m_Age = age;
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
	if (m_Residence == nullptr) return 0;
	float taxSatisfaction = 0;
	float residenceSatisfaction = 0;
	float workplaceSatisfaction = 0;
	if (m_Workplace == nullptr) {
		taxSatisfaction = 1 - (m_Residence->GetTaxRatePercentage() / 100) - 0.5;
		if (taxSatisfaction < 0) taxSatisfaction = 0;
		workplaceSatisfaction = 0;
	}
	else {
		float test1 = m_Workplace->GetTaxRatePercentage() + m_Residence->GetTaxRatePercentage();
		taxSatisfaction = 1 - (m_Workplace->GetTaxRatePercentage() + m_Residence->GetTaxRatePercentage()) / 2 / 100;
		workplaceSatisfaction = m_Workplace->Get_Satisfaction();
	}
	residenceSatisfaction = m_Residence->Get_Satisfaction();
	
	return taxSatisfaction * 0.3 + residenceSatisfaction * 0.5 + workplaceSatisfaction * 0.2;
}

float Citizen::PayTax()
{
	float educationRate = m_Education == BASIC ? 1.2f : (m_Education == INTERMEDIATE ? 1.5f : 2.0f);

	if (IsPensioner())
	{
		//std::cout << "A citizen at the age of: " << Get_Age() << " got " << ((m_Pension / m_monthsBeforePension) / 2) << " pension\n";
		return -((m_Pension / m_monthsBeforePension) / 2);
	}
	else
	{
		float workPlaceTax = m_Workplace == nullptr ? 0.0f : m_Workplace->GetTaxRate() / 12.0f;
		float homeTax = m_Residence == nullptr ? 0.0f : m_Residence->GetTaxRate() / 12.0f;

		float tax = (workPlaceTax + homeTax) * educationRate;

		if (m_Age >= 45)
		{
			++m_monthsBeforePension;
			m_Pension += tax;
		}

		return tax;
	}
}