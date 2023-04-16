#ifndef FIRESTATION_H
#define FIRESTATION_H

#include "Building.h"

class FireStation : public Building
{
public:
    FireStation(FieldType type, int x, int y, float cost) : Building(type, x, y, cost) {};
    ~FireStation() {}

    bool inline IsFireStation() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 1; }
};

#endif