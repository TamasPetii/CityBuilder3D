#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "Building.h"

class PoliceStation : public Building
{
public:
    PoliceStation(FieldType type, FieldDirection direction, int x, int y) : Building(type, direction, x, y) {};
    ~PoliceStation() {}

    bool inline IsPoliceStation() const override { return true; }
    //Azért 0, mert a közbiztonságot külön számoljuk
    float inline GetBuildingSatisfaction() const override { return 0; }
};

#endif
