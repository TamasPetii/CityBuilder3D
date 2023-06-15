#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

static bool CHANGED = false;

/**
 * Constructs a GameField object with the specified parameters.
 *
 * @param type The type of the field.
 * @param direction The direction of the field.
 * @param x The x-coordinate of the field.
 * @param y The y-coordinate of the field.
 *
 * @returns None
 */
GameField::GameField(FieldType type, FieldDirection direction, int x, int y) :
	m_Type(type),
	m_Direction(direction),
	m_X(x),
	m_Y(y)
{
	m_FireRate = 0;
	m_BuildCost = CalculateBuildCost(type);
	m_AnnualCost = CalculateAnnualCost(type);
	m_SatisfactionPoints = 0;
}

/**
 * Creates a new GameField object based on the given parameters.
 *
 * @param type The type of the field to create.
 * @param direction The direction of the field to create.
 * @param x The x-coordinate of the field to create.
 * @param y The y-coordinate of the field to create.
 *
 * @returns A pointer to the newly created GameField object.
 *          Returns nullptr if the type is invalid.
 */
GameField* GameField::CreateField(FieldType type, FieldDirection direction, int x, int y)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return new ResidentalArea(LEVEL_1, type, direction, x, y);
	case RESIDENTIAL_LVL2: return new ResidentalArea(LEVEL_2, type, direction, x, y);
	case RESIDENTIAL_LVL3: return new ResidentalArea(LEVEL_3, type, direction, x, y);
	case INDUSTRIAL_LVL1: return new IndustrialArea(LEVEL_1, type, direction, x, y);
	case INDUSTRIAL_LVL2: return new IndustrialArea(LEVEL_2, type, direction, x, y);
	case INDUSTRIAL_LVL3: return new IndustrialArea(LEVEL_3, type, direction, x, y);
	case SERVICE_LVL1: return new ServiceArea(LEVEL_1, type, direction, x, y);
	case SERVICE_LVL2: return new ServiceArea(LEVEL_2, type, direction, x, y);
	case SERVICE_LVL3: return new ServiceArea(LEVEL_3, type, direction, x, y);
	case EMPTY: return new Empty(type, direction, x, y);
	case ROAD: return new Road(type, direction, x, y);
	case FOREST: return new Forest(type, direction, x, y);
	case LAKE: return new Lake(type, direction, x, y);
	case POLICESTATION: return new PoliceStation(type, direction, x, y);
	case FIRESTATION: return new FireStation(type, direction, x, y);
	case HIGHSCHOOL: return new HighSchool(type, direction, x, y);
	case UNIVERSITY: return new University(type, direction, x, y);
	case STADIUM: return new Stadium(type, direction, x, y);
	case POWERSTATION: return new PowerStation(type, direction, x, y);
	case POWERWIRE: return new PowerWire(type, direction, x, y);
	case CRATER: return new Crater(type, direction, x, y);
	default: return nullptr;
	}
}

/**
 * Converts a FieldType enum value to its corresponding string representation.
 *
 * @param type The FieldType enum value to convert.
 *
 * @returns The string representation of the FieldType enum value.
 */
std::string GameField::ConvertTypeToStr(FieldType type)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return "Residential Area (LVL1)";
	case RESIDENTIAL_LVL2: return "Residential Area (LVL2)";
	case RESIDENTIAL_LVL3: return "Residential Area (LVL3)";
	case INDUSTRIAL_LVL1: return "Industrial Area (LVL1)";
	case INDUSTRIAL_LVL2: return "Industrial Area (LVL2)";
	case INDUSTRIAL_LVL3: return "Industrial Area (LVL3)";
	case SERVICE_LVL1: return "Service Area (LVL1)";
	case SERVICE_LVL2: return "Service Area (LVL2)";
	case SERVICE_LVL3: return "Service Area (LVL3)";
	case EMPTY: return "Emtpy";
	case ROAD: return "Road";
	case FOREST: return "Forest";
	case LAKE: return "Lake";
	case POLICESTATION: return "PoliceStation";
	case FIRESTATION: return "FireStation";
	case HIGHSCHOOL: return "HighSchool";
	case UNIVERSITY: return "University";
	case STADIUM: return "Stadium";
	case POWERSTATION: return "PowerStation";
	case POWERWIRE: return "PowerWire";
	case CRATER: return "Crater (Meteor)";
	}

	return "";
}

/**
 * Calculates the build cost of a given field type.
 *
 * @param type The type of field to calculate the build cost for.
 *
 * @returns The build cost of the given field type in thousands of currency units.
 */
int GameField::CalculateBuildCost(FieldType type)
{
	int cost;

	switch (type)
	{
	case RESIDENTIAL_LVL1: cost = 100; break;
	case RESIDENTIAL_LVL2: cost = 165; break;
	case RESIDENTIAL_LVL3: cost = 486; break;
	case INDUSTRIAL_LVL1: cost = 144; break;
	case INDUSTRIAL_LVL2: cost = 215; break;
	case INDUSTRIAL_LVL3: cost = 625; break;
	case SERVICE_LVL1: cost = 192; break;
	case SERVICE_LVL2: cost = 240; break;
	case SERVICE_LVL3: cost = 750; break;
	case ROAD: cost = 25; break;
	case FOREST: cost = 5; break;
	case POLICESTATION: cost = 145; break;
	case FIRESTATION: cost = 165; break;
	case HIGHSCHOOL: cost = 85; break;
	case UNIVERSITY: cost = 135; break;
	case STADIUM: cost = 285; break;
	case POWERSTATION: cost = 225; break;
	case CRATER: cost = 35; break;
	default: cost = 0; break;
	}

	return cost * 1000;
}

/**
 * Calculates the annual cost of maintaining a field of a given type.
 *
 * @param type The type of field to calculate the annual cost for.
 *
 * @returns The annual cost of maintaining the field.
 */
int GameField::CalculateAnnualCost(FieldType type)
{
	return static_cast<int>(CalculateBuildCost(type) * 0.05);
}

/**
 * Converts a GameField object to a string representation.
 *
 * @param field A pointer to the GameField object to be converted.
 *
 * @returns A string representation of the GameField object.
 */
std::string GameField::ToString(GameField* field)
{
	std::stringstream ss;

	ss << "Type: " << GameField::ConvertTypeToStr(field->m_Type) << std::endl;
	ss << "Coord: [" << field->m_X << "," << field->m_Y << "]" << std::endl;
	ss << "Build Cost: " << field->m_BuildCost << std::endl;
	ss << "Annual Cost: " << field->m_AnnualCost << std::endl;

	return ss.str();
}

/**
 * Randomly sets the game field on fire based on the fire rate.
 *
 * @returns None
 */
void GameField::RandomFire()
{
	if (m_OnFire) return;

	m_OnFire = (rand() % (int)(350000 + 2250 * m_FireRate) == 123450);
}