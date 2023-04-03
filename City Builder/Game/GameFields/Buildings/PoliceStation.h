#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "Building.h"

class PoliceStation : public Building
{
public:
    PoliceStation() : Building() {};
    ~PoliceStation() {}

    bool inline IsPoliceStation() const override { return true; }
};

#endif
