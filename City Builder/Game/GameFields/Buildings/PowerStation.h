#ifndef POWERSTATION_H
#define POWERSTATION_H

#include "Building.h"

class PowerStation : public Building
{
public:
    PowerStation(FieldType type, int x, int y, float cost) : Building(type, x, y, cost) {};
    ~PowerStation() {}

    bool inline IsPowerStation() const override { return true; }
};

#endif
