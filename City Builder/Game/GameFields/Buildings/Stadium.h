#ifndef STADIUM_H
#define STADIUM_H

#include "Building.h"

class Stadium : public Building
{
public:
    Stadium(float cost) : Building(cost) {};
    ~Stadium() {}

    bool inline IsStadium() const override { return true; }
};

#endif
