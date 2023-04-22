#ifndef POWERWIRE_H
#define POWERWIRE_H

#include "Building.h"

class PowerWire : public Building
{
public:
    PowerWire(FieldType type, int x, int y, float cost) : Building(type, x, y, cost) {};
    ~PowerWire() {}

    bool inline IsPowerWire() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 0; }
};

#endif
