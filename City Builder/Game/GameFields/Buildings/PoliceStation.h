#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "Building.h"

class PoliceStation : public Building
{
public:
    PoliceStation(float cost) : Building(cost) {};
    ~PoliceStation() {}

    bool inline IsPoliceStation() const override { return true; }
};

#endif
