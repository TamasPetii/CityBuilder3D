#include "Citizen.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include <iostream>


//--------------------------------------------------------STATIC--------------------------------------------------------//

int Citizen::COUNTER = 0;
int Citizen::MIN_AGE = 18;
int Citizen::MAX_AGE = 60;
int Citizen::MONEY_SATISFACTION = 0;
std::stringstream Citizen::LOG;

void Citizen::WRITE_LOG(std::string str, Citizen* citizen, Zone* zone)
{
	LOG << str << " | Citizen [" << citizen << "] | " << GameField::ConvertTypeToStr(zone->Get_Type()) << "[" << zone << "]" << std::endl;
}

std::string Citizen::ToString(Citizen* citizen)
{
	std::stringstream ss;

	ss << "Citizen: " << citizen << std::endl;
	ss << "Age: " << citizen->m_Age << std::endl;
	ss << "Education: " << Citizen::ConvertEducationToString(citizen->m_Education) << std::endl;
	ss << "Satisfaction: " << citizen->Calculate_Satisfaction() * 100 << std::endl;
	ss << "Residence: " << citizen->m_Residence << std::endl;
	ss << "Workplace: " << citizen->m_Workplace << std::endl;

	return ss.str();
}

std::string Citizen::ConvertEducationToString(enum Education e)
{
	switch (e)
	{
	case BASIC: return "BASIC";
	case INTERMEDIATE: return "INTERMEDIATE";
	case ADVANCED: return "ADVANCED";
	}
	return "";
}

//--------------------------------------------------------NORMAL--------------------------------------------------------//

Citizen::Citizen()
{
	m_Age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
	m_Pension = 0;
	m_MonthsBeforePension = 0;
	m_Education = BASIC;
	m_Residence = nullptr;
	m_Workplace = nullptr;

	COUNTER++;
}

Citizen::~Citizen()
{
	COUNTER--;
}

void Citizen::JoinZone(Zone* zone)
{
	if (zone == m_Residence || zone == m_Workplace) return;

	zone->JoinZone(this);

	if (zone->IsResidentalArea())
	{
		m_Residence = dynamic_cast<ResidentalArea*>(zone);
		WRITE_LOG("JOIN", this, m_Residence);
	}

	if (zone->IsWorkingArea())
	{
		m_Workplace = dynamic_cast<WorkingArea*>(zone);
		WRITE_LOG("JOIN", this, m_Workplace);
	}
}

void Citizen::LeaveResidence()
{
	if (m_Residence == nullptr) return;

	WRITE_LOG("LEAVE", this, m_Residence);
	m_Residence->LeaveZone(this);
	m_Residence = nullptr;
}

void Citizen::LeaveWorkplace()
{
	if (m_Workplace == nullptr) return;

	WRITE_LOG("LEAVE", this, m_Workplace);
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
		WRITE_LOG("LEAVE (DELETE)", this, m_Residence);
		m_Residence = nullptr;
	}

	if (zone->IsWorkingArea())
	{
		WRITE_LOG("LEAVE (DELETE)", this, m_Workplace);
		m_Workplace = nullptr;
	}
}

float Citizen::Calculate_Distance(Zone* zone1, Zone* zone2)
{
	if (zone1 == nullptr || zone2 == nullptr) return 0;

	return sqrtf(pow(zone1->Get_X() - zone2->Get_X(), 2) + pow(zone1->Get_Y() - zone2->Get_Y(), 2));
}

float Citizen::Calculate_ZoneSatisfaction(Zone* zone)
{
	if (zone == nullptr) return 0;

	float Satisfaction_Tax = 1 - zone->Calculate_TaxRatePercentage() / 100;
	float Satisfaction = zone->Calculate_NormalSatisfaction();

	float Ratio_Tax = zone->IsResidentalArea() ? 0.25f : 0.45f;
	float Ratio = zone->IsResidentalArea() ? 0.75f : 0.55f;

	return Satisfaction_Tax * Ratio_Tax + Satisfaction * Ratio;
}

float Citizen::Calculate_Satisfaction()
{
	float Satisfaction_Residence = Calculate_ZoneSatisfaction(m_Residence);
	float Satisfaction_Workplace = Calculate_ZoneSatisfaction(m_Workplace);
	float Satisfaction_Disctance = Calculate_Distance(m_Residence, m_Workplace);
	float Satisfaction_Money = MONEY_SATISFACTION < 0 ? (MONEY_SATISFACTION / 1000000.f * 0.1f) - 0.15f : 0.f;
	Satisfaction_Disctance = Satisfaction_Disctance < 20 ? Satisfaction_Disctance : 20;
	
	float Satisfaction = (Satisfaction_Residence + Satisfaction_Workplace) / 2 * 0.9f + 0.1f * Satisfaction_Disctance / 20 + Satisfaction_Money;
	Satisfaction = Satisfaction < -1 ? -1 : Satisfaction;

	return Satisfaction;
}

void Citizen::Increase_EducationLevel(Education maxEducationLevel)
{
	if (m_Education == Education::BASIC && maxEducationLevel != Education::BASIC)
	{
		m_Education = Education::INTERMEDIATE;
	}
	else if (m_Education == Education::INTERMEDIATE && maxEducationLevel == Education::ADVANCED)
	{
		m_Education = Education::ADVANCED;
	}
}

float Citizen::PayTax()
{
	float educationRate = m_Education == BASIC ? 1.2f : (m_Education == INTERMEDIATE ? 1.5f : 2.0f);

	if (IsPensioner())
	{
		return -1 * ((m_Pension / m_MonthsBeforePension) / 2);
	}
	else
	{
		float Workplace_Tax = m_Workplace == nullptr ? 0.0f : m_Workplace->Calculate_TaxRate();
		float Residence_Tax = m_Residence == nullptr ? 0.0f : m_Residence->Calculate_TaxRate();
		float Tax = (Workplace_Tax + Residence_Tax) * educationRate;

		if (m_Age >= 45)
		{
			++m_MonthsBeforePension;
			m_Pension += Tax;
		}

		return Tax;
	}
}
