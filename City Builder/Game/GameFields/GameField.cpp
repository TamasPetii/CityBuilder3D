#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

GameField* GameField::CreateField(FieldType type, int x, int y)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return new ResidentalArea(LEVEL_1, type, x, y, 250);
	case RESIDENTIAL_LVL2: return new ResidentalArea(LEVEL_2, type, x, y, 350);
	case RESIDENTIAL_LVL3: return new ResidentalArea(LEVEL_3, type, x, y, 450);
	case INDUSTRIAL_LVL1: return new IndustrialArea(LEVEL_1, type, x, y, 225);
	case INDUSTRIAL_LVL2: return new IndustrialArea(LEVEL_2, type, x, y, 325);
	case INDUSTRIAL_LVL3: return new IndustrialArea(LEVEL_3, type, x, y, 425);
	case SERVICE_LVL1: return new ServiceArea(LEVEL_1, type, x, y, 225);
	case SERVICE_LVL2: return new ServiceArea(LEVEL_2, type, x, y, 325);
	case SERVICE_LVL3: return new ServiceArea(LEVEL_3, type, x, y, 425);
	case EMPTY: return new Empty(type, x, y, 0.0);
	case ROAD: return new Road(type, x, y, 50);
	case FOREST: return new Forest(type, x, y, 5);
	case LAKE: return new Lake(type, x, y, 5);
	case POLICESTATION: return new PoliceStation(type, x, y, 125);
	case FIRESTATION: return new FireStation(type, x, y, 135);
	case HIGHSCHOOL: return new HighSchool(type, x, y, 175);
	case UNIVERSITY: return new University(type, x, y, 275);
	case STADIUM: return new Stadium(type, x, y, 1025);
	case POWERSTATION: return new PowerStation(type, x, y, 785);
	case POWERWIRE: return new PowerWire(type, x, y, 155);
	case CRATER: return new Crater(type, x, y, 50.f);
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
	}

	return "";
}

void GameField::RandomFire()
{
	if (m_OnFire) return;

	m_OnFire = (rand() % 10000 == 123);
}