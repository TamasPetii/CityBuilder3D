#include "Building.h"

/**
 * Returns a string representation of a Building object.
 *
 * @param building A pointer to the Building object to be converted to a string.
 *
 * @returns A string representation of the Building object.
 */
std::string Building::ToString(Building* building)
{
	std::stringstream ss;

	ss << GameField::ToString(building);
	ss << "Satisfaction Boost: " << building->GetBuildingSatisfaction() << std::endl;

	return ss.str();
}