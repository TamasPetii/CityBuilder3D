#ifndef FIRESTATION_H
#define FIRESTATION_H

#include "Building.h"

class FireStation : public Building
{
public:
    FireStation(float cost) : Building(cost) {};
    ~FireStation() {}

    bool inline IsFireStation() const override { return true; }
};

#endif