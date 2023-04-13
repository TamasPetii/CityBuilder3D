#ifndef POWERSTATION_H
#define POWERSTATION_H

#include "Building.h"

class PowerStation : public Building
{
public:
    PowerStation(float cost) : Building(cost) {};
    ~PowerStation() {}

    bool inline IsPowerStation() const override { return true; }
};

#endif
