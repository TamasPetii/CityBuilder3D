#include "Zone.h"

Zone::Zone(Level level, FieldType type, int x, int y, float cost)
	: GameField(type, x, y, cost)
{
	m_details.level = level;
	m_details.contain = 0;
	m_details.satisfaction = 0;
	m_details.safety = 0;
	m_details.industrial_penalty = 0;

	AdjustCapacity();
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
	return 0;
}

//teszteléshez metódus
float Zone::Get_RawSatisfaction() const {
	return m_details.satisfaction + m_details.forest_satisfaction + m_details.safety + m_details.industrial_penalty;
}

void Zone::AdjustCapacity()
{
	if (m_details.level == LEVEL_1)
	{
		m_details.capacity = 4;
	}
	if (m_details.level == LEVEL_2)
	{
		m_details.capacity = 8;
	}
	if (m_details.level == LEVEL_3)
	{
		m_details.capacity = 16;
	}
}

bool Zone::UpgradeZone()
{
	if (m_details.level == LEVEL_3) return false;

	m_details.level = (Level)((int)m_details.level + 1);
	m_Type = (FieldType)((int)m_Type + 1);

	AdjustCapacity();

	return true;
}

int Zone::Get_UpgradeFee()
{
	//TODO: Adjust fees
	if (m_details.level == LEVEL_2)
	{
		return 100;
	}
	else
	{
		return 300;
	}

}

Citizen* Zone::GetRandomDriver()
{
	double probability = (m_details.contain + 1) * 0.001;
	double random = (double)rand() / RAND_MAX;

	if (random < probability && m_citizens.size() > 0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, m_citizens.size() - 1);
		auto random_it = std::next(std::begin(m_citizens), dis(gen));

		return *random_it;
	}
	else
	{
		return nullptr;
	}
}