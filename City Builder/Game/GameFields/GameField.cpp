#include "GameField.h"
#include "Buildings/_BuildingHeaders.h"
#include "General/_GeneralHeaders.h"
#include "Zones/_ZoneHeaders.h"

GameField* GameField::CreateField(FieldType type, int x, int y)
{
	switch (type)
	{
	case RESIDENTIAL_LVL1: return new ResidentalArea(LEVEL_1, type, x, y, 0.0);
	case RESIDENTIAL_LVL2: return new ResidentalArea(LEVEL_2, type, x, y, 0.0);
	case RESIDENTIAL_LVL3: return new ResidentalArea(LEVEL_3, type, x, y, 0.0);
	case INDUSTRIAL_LVL1: return new IndustrialArea(LEVEL_1, type, x, y, 0.0);
	case INDUSTRIAL_LVL2: return new IndustrialArea(LEVEL_2, type, x, y, 0.0);
	case INDUSTRIAL_LVL3: return new IndustrialArea(LEVEL_3, type, x, y, 0.0);
	case SERVICE_LVL1: return new ServiceArea(LEVEL_1, type, x, y, 0.0);
	case SERVICE_LVL2: return new ServiceArea(LEVEL_2, type, x, y, 0.0);
	case SERVICE_LVL3: return new ServiceArea(LEVEL_3, type, x, y, 0.0);
	case EMPTY: return new Empty(type, x, y, 0.0);
	case ROAD: return new Road(type, x, y, 0.0);
	case FOREST: return new Forest(type, x, y, 0.0);
	case POLICESTATION: return new PoliceStation(type, x, y, 0.0);
	case FIRESTATION: return new FireStation(type, x, y, 0.0);
	case HIGHSCHOOL: return new HighSchool(type, x, y, 0.0);
	case UNIVERSITY: return new University(type, x, y, 0.0);
	case STADIUM: return new Stadium(type, x, y, 0.0);
	case POWERSTATION: return new PowerStation(type, x, y, 0.0);
	case POWERWIRE: return new PowerWire(type, x, y, 0.0);
	}
}