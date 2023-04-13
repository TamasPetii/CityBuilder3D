#ifndef POWERWIRE_H
#define POWERWIRE_H

#include "Building.h"

class PowerWire : public Building
{
public:
    PowerWire(float cost) : Building(cost) {};
    ~PowerWire() {}

    bool inline IsPowerWire() const override { return true; }
};

#endif
