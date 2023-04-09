#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"

Citizen::Citizen()
{
	m_Education = BASIC;
	m_Age = 18;
}

void Citizen::JoinZone(Zone* zone)
{

}

void Citizen::LeaveZone(Zone* zone)
{

}

void Citizen::ChangeZone(Zone* zone)
{

}

void Citizen::DeleteZone(Zone* zone)
{

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