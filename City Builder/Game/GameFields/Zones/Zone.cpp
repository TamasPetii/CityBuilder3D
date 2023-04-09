#include "Zone.h"

Zone::Zone(Level level) : GameField()
{
	m_details.level = level;
	m_details.contain = 0;
	
	//TODO: Adjust the zone capacities
	if (level == LEVEL_1)
	{
		m_details.capacity = 20;
	}
	if (level == LEVEL_2)
	{
		m_details.capacity = 50;
	}
	if (level == LEVEL_2)
	{
		m_details.capacity = 100;
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