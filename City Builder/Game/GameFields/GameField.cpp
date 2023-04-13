#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

GameField* GameField::CreateField(FieldType type)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return new ResidentalArea(LEVEL_1, 0.0);
	case RESIDENTIAL_LVL2: return new ResidentalArea(LEVEL_2, 0.0);
	case RESIDENTIAL_LVL3: return new ResidentalArea(LEVEL_3, 0.0);
	case INDUSTRIAL_LVL1: return new IndustrialArea(LEVEL_1, 0.0);
	case INDUSTRIAL_LVL2: return new IndustrialArea(LEVEL_2, 0.0);
	case INDUSTRIAL_LVL3: return new IndustrialArea(LEVEL_3, 0.0);
	case SERVICE_LVL1: return new ServiceArea(LEVEL_1, 0.0);
	case SERVICE_LVL2: return new ServiceArea(LEVEL_2, 0.0);
	case SERVICE_LVL3: return new ServiceArea(LEVEL_3, 0.0);
	case EMPTY: return new Empty(0.0);
	case ROAD: return new Road(0.0);
	case FOREST: return new Forest(0.0);
	case POLICESTATION: return new PoliceStation(0.0);
	case FIRESTATION: return new FireStation(0.0);
	case HIGHSCHOOL: return new HighSchool(0.0);
	case UNIVERSITY: return new University(0.0);
	case STADIUM: return new Stadium(0.0);
	case POWERSTATION: return new PowerStation(0.0);
	case POWERWIRE: return new PowerWire(0.0);
	}
}

float GameField::Get_SatisfactionPoints() const
{
	return 0;
}

float GameField::Get_Fee() const
{
	return 0;
}

float GameField::Get_Cost() const
{
	return 0;
}