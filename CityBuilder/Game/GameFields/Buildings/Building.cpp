#include "Building.h"

std::string Building::ToString(Building* building)
{
	std::stringstream ss;

	ss << GameField::ToString(building);
	ss << "Satisfaction Boost: " << building->GetBuildingSatisfaction() << std::endl;

	return ss.str();
}