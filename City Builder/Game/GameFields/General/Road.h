#ifndef ROAD_H
#define ROAD_H

#include "../GameField.h"

class Road : public GameField
{
public:
    Road(float cost) : GameField(cost) {};
    ~Road() {}

    bool inline IsRoad() const override { return true; }
};

#endif