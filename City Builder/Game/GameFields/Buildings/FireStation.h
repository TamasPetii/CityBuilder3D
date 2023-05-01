#ifndef FIRESTATION_H
#define FIRESTATION_H

#include "Building.h"

class FireStation : public Building
{
public:
    FireStation(FieldType type, FieldDirection direction, int x, int y) : Building(type, direction, x, y) {};
    ~FireStation() {}

    bool inline IsFireStation() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 1; }
};

#endif