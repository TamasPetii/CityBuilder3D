#ifndef LAKE_H
#define LAKE_H

#include "../GameField.h"

class Lake : public GameField
{
public:
    Lake(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Lake() {}

    bool inline IsLake() const override { return true; }
};

#endif