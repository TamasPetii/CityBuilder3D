#ifndef POWERWIRE_H
#define POWERWIRE_H

#include "Building.h"

class PowerWire : public Building
{
public:
    PowerWire() : Building() {};
    ~PowerWire() {}

    bool inline IsPowerWire() const override { return true; }
};

#endif
