#ifndef POWERWIRE_H
#define POWERWIRE_H

#include "Building.h"

class PowerWire : public Building
{
public:
    PowerWire(FieldType type, FieldDirection direction, int x, int y) : Building(type, direction, x, y) {};
    ~PowerWire() {}

    bool inline IsPowerWire() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 0; }
};

#endif
