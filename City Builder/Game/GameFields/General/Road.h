#ifndef ROAD_H
#define ROAD_H

#include "../GameField.h"

class Road : public GameField
{
public:
    Road(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};
    ~Road() {}

    bool inline IsRoad() const override { return true; }
};

#endif