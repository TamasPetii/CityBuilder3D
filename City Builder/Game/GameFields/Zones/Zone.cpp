#include "Zone.h"

Zone::Zone(Level level, FieldType type, int x, int y, float cost) 
	: GameField(type, x, y, cost)
{
	m_details.level = level;
	m_details.contain = 0;
	m_details.stadiumBonus = false;
	m_details.policeBonus = false;
	m_details.industrialPenalty = 0;

	//TODO: Adjust the zone capacities
	if (level == LEVEL_1)
	{
		m_details.capacity = 4;
	}
	if (level == LEVEL_2)
	{
		m_details.capacity = 8;
	}
	if (level == LEVEL_3)
	{
		m_details.capacity = 16;
	}
}


void Zone::JoinZone(Citizen* citizen)
{
	m_citizens.insert(citizen);
	++m_details.contain;
}

void Zone::LeaveZone(Citizen* citizen)
{
	m_citizens.erase(citizen);
	--m_details.contain;
}

void Zone::DeleteZone()
{
	for (auto it = m_citizens.begin(); it != m_citizens.end(); ++it)
	{
		(*it)->DeletedZone(this);
	}
}

std::string Zone::Get_CitizenDetails()
{
	int i = 1;
	std::stringstream ss;

	for (auto citizen : m_citizens)
	{
		ss << i << ". " << citizen << "\n";
		i++;
	}

	return ss.str();
}

float Zone::Get_Satisfaction() const {
	float satisfaction = 0;
	if (m_details.policeBonus) satisfaction += 0.7;
	if (m_details.stadiumBonus) satisfaction += 0.3;
	satisfaction -= m_details.industrialPenalty;
	if (satisfaction < 0) satisfaction = 0;
	return satisfaction;
}