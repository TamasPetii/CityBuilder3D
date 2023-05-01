#include "Zone.h"

bool Zone::CHANGED = false;

Zone::Zone(Level level, FieldType type, FieldDirection direction, int x, int y) :
	GameField(type, direction, x, y)
{
	m_Level = level;
	m_Contain = 0;
	m_ForestSatisfaction = 0;
	m_Satisfaction = 0;
	m_Safety = 0;
	m_IndustrialPenalty = 0;

	AdjustCapacity();
}


void Zone::JoinZone(Citizen* citizen)
{
	m_citizens.insert(citizen);
	++m_Contain;

	CHANGED = true;
}

void Zone::LeaveZone(Citizen* citizen)
{
	m_citizens.erase(citizen);
	--m_Contain;

	CHANGED = true;
}

void Zone::DeleteZone()
{
	for (auto it = m_citizens.begin(); it != m_citizens.end(); ++it)
	{
		(*it)->DeletedZone(this);
	}

	CHANGED = true;
}

//teszteléshez metódus
float Zone::Calculate_RawSatisfaction() const {
	//TODO FOREST
	return m_Satisfaction + m_Safety + m_IndustrialPenalty + m_ForestSatisfaction;
}

float Zone::Calculate_RealSatisfaction() const
{
	float Satisfaction = 0;

	for (auto citizen : m_citizens)
	{
		Satisfaction += citizen->Calculate_Satisfaction();
	}

	return Satisfaction / m_Contain;
}

void Zone::AdjustCapacity()
{
	if (m_Level == LEVEL_1)
	{
		m_Capacity = 4;
	}
	if (m_Level == LEVEL_2)
	{
		m_Capacity = 8;
	}
	if (m_Level == LEVEL_3)
	{
		m_Capacity = 16;
	}
}

bool Zone::UpgradeZone()
{
	if (m_Level == LEVEL_3) return false;

	m_Level = (Level)((int)m_Level + 1);
	m_Type = (FieldType)((int)m_Type + 1);

	m_BuildCost = CalculateBuildCost(m_Type);
	m_AnnualCost = CalculateAnnualCost(m_Type);

	AdjustCapacity();
	CHANGED = true;

	return true;
}

Citizen* Zone::GetRandomDriver()
{
	double probability = (m_Contain + 1) * 0.001;
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

std::string Zone::ToString(Zone* zone)
{
	std::stringstream ss;

	ss << GameField::ToString(zone);
	ss << "Contain: " << zone->m_Contain << std::endl;
	ss << "Capacity: " << zone->m_Capacity << std::endl;
	ss << "Tax: " << zone->Calculate_TaxRate() << std::endl;
	ss << "Tax %: " << zone->Calculate_TaxRatePercentage() << std::endl;
	ss << "Forest Boost: " << zone->Get_ForestSatisfaction() << std::endl;
	ss << "Safety: " << zone->Get_Safety() << std::endl;
	ss << "Industrial Penalty: " << zone->Get_IndustrialPenalty() << std::endl;
	ss << "Normal Satisfaction: " << zone->Calculate_NormalSatisfaction() * 100 << std::endl;
	ss << "Real Satisfaction: " << zone->Calculate_RealSatisfaction() * 100 << std::endl;
	
	int i = 0;
	for (auto citizen : zone->Get_Citizens())
	{
		ss << "|" << ++i << ".|~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		ss << Citizen::ToString(citizen);
	}

	return ss.str();
}