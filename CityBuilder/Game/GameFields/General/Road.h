#ifndef ROAD_H
#define ROAD_H

#include "../GameField.h"

class Road : public GameField
{
public:
    Road(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Road() {}

    bool inline IsRoad() const override { return true; }
};

#endif