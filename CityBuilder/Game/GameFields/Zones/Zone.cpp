#include "Zone.h"

bool Zone::CHANGED = false;

/**
 * Constructs a new Zone object with the specified parameters.
 *
 * @param level The level of the zone.
 * @param type The type of the zone.
 * @param direction The direction of the zone.
 * @param x The x-coordinate of the zone.
 * @param y The y-coordinate of the zone.
 *
 * @returns None
 */
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


/**
 * Adds a Citizen to the Zone and increments the count of contained Citizens.
 *
 * @param citizen A pointer to the Citizen to be added to the Zone.
 *
 * @returns None
 */
void Zone::JoinZone(Citizen* citizen)
{
	m_citizens.insert(citizen);
	++m_Contain;

	CHANGED = true;
}

/**
 * Removes a citizen from the zone.
 *
 * @param citizen A pointer to the citizen to be removed.
 *
 * @returns None
 */
void Zone::LeaveZone(Citizen* citizen)
{
	m_citizens.erase(citizen);
	--m_Contain;

	CHANGED = true;
}

/**
 * Deletes the current zone and notifies all citizens that belong to this zone.
 *
 * @param None
 *
 * @returns None
 */
void Zone::DeleteZone()
{
	for (auto it = m_citizens.begin(); it != m_citizens.end(); ++it)
	{
		(*it)->DeletedZone(this);
	}

	CHANGED = true;
}


/**
 * Calculates the raw satisfaction score for a zone.
 *
 * The raw satisfaction score is the sum of the satisfaction, safety, industrial penalty, and forest satisfaction scores.
 *
 * @returns The raw satisfaction score for the zone.
 */
float Zone::Calculate_RawSatisfaction() const {
	return m_Satisfaction + m_Safety + m_IndustrialPenalty + m_ForestSatisfaction;
}

/**
 * Calculates the real satisfaction of the zone by computing the average satisfaction of all citizens in the zone.
 *
 * @returns The real satisfaction of the zone.
 */
float Zone::Calculate_RealSatisfaction() const
{
	float Satisfaction = 0;

	for (auto citizen : m_citizens)
	{
		Satisfaction += citizen->Calculate_Satisfaction();
	}

	return Satisfaction / m_Contain;
}

/**
 * Adjusts the capacity of the Zone based on its level.
 *
 * @param None
 *
 * @returns None
 */
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

/**
 * Upgrades the zone to the next level and type, if possible.
 *
 * @returns True if the zone was upgraded, false otherwise.
 */
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

/**
 * Returns a random Citizen from the Zone's list of citizens.
 * The probability of returning a Citizen is based on the number of citizens in the Zone.
 *
 * @returns A pointer to a randomly selected Citizen, or nullptr if the Zone has no citizens.
 */
Citizen* Zone::GetRandomDriver()
{
	double probability = (m_Contain + 1) * 0.001;
	double random = (double)rand() / RAND_MAX;

	if (random < probability && m_citizens.size() > 0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, (int)m_citizens.size() - 1);
		auto random_it = std::next(std::begin(m_citizens), dis(gen));

		return *random_it;
	}
	else
	{
		return nullptr;
	}
}

/**
 * Returns a string representation of the Zone object.
 *
 * @param zone A pointer to the Zone object to be converted to a string.
 *
 * @returns A string representation of the Zone object.
 */
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
	ss << "Fire Rate: " << zone->Get_FireRate() << std::endl;
	
	int i = 0;
	for (auto citizen : zone->Get_Citizens())
	{
		ss << "|" << ++i << ".|~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		ss << Citizen::ToString(citizen);
	}

	return ss.str();
}