#ifndef STADIUM_H
#define STADIUM_H

#include "Building.h"

class Stadium : public Building
{
public:
    Stadium(FieldType type, int x, int y, float cost) : Building(type, x, y, cost) {};
    ~Stadium() {}

    bool inline IsStadium() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 2; }
};

#endif
