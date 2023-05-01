#ifndef POWERSTATION_H
#define POWERSTATION_H

#include "Building.h"

class PowerStation : public Building
{
public:
    PowerStation(FieldType type, FieldDirection direction, int x, int y) : Building(type, direction, x, y) {};
    ~PowerStation() {}

    bool inline IsPowerStation() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 1; }
};

#endif
