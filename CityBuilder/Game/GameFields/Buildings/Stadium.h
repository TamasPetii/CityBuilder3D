#ifndef STADIUM_H
#define STADIUM_H

#include "Building.h"

class Stadium : public Building
{
public:
    Stadium(FieldType type, FieldDirection direction, int x, int y) : Building(type, direction, x, y) {};
    ~Stadium() {}

    bool inline IsStadium() const override { return true; }
    float inline GetBuildingSatisfaction() const override { return 2; }
};

#endif
