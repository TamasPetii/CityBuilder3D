#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

GameField::GameField(FieldType type, FieldDirection direction, int x, int y) :
	m_Type(type),
	m_Direction(direction),
	m_X(x),
	m_Y(y)
{
	m_BuildCost = CalculateBuildCost(type);
	m_AnnualCost = CalculateAnnualCost(type);
	m_SatisfactionPoints = 0;
}

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

int GameField::CalculateAnnualCost(FieldType type)
{
	return CalculateBuildCost(type) * 0.05;
}

std::string GameField::ToString(GameField* field)
{
	std::stringstream ss;

	ss << "Type: " << GameField::ConvertTypeToStr(field->m_Type) << std::endl;
	ss << "Coord: [" << field->m_X << "," << field->m_Y << "]" << std::endl;
	ss << "Build Cost: " << field->m_BuildCost << std::endl;
	ss << "Annual Cost: " << field->m_AnnualCost << std::endl;

	return ss.str();
}