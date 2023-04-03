#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

GameField* GameField::CreateField(FieldType type)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return new ResidentalArea(LEVEL_1);
	case RESIDENTIAL_LVL2: return new ResidentalArea(LEVEL_2);
	case RESIDENTIAL_LVL3: return new ResidentalArea(LEVEL_3);
	case INDUSTRIAL_LVL1: return new IndustrialArea(LEVEL_1);
	case INDUSTRIAL_LVL2: return new IndustrialArea(LEVEL_2);
	case INDUSTRIAL_LVL3: return new IndustrialArea(LEVEL_3);
	case SERVICE_LVL1: return new ServiceArea(LEVEL_1);
	case SERVICE_LVL2: return new ServiceArea(LEVEL_2);
	case SERVICE_LVL3: return new ServiceArea(LEVEL_3);
	case EMPTY: return new Empty();
	case ROAD: return new Road();
	case FOREST: return new Forest();
	case POLICESTATION: return new PoliceStation();
	case FIRESTATION: return new FireStation();
	case HIGHSCHOOL: return new HighSchool();
	case UNIVERSITY: return new University();
	case STADIUM: return new Stadium();
	case POWERSTATION: return new PowerStation();
	case POWERWIRE: return new PowerWire();
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