#ifndef LAKE_H
#define LAKE_H

#include "../GameField.h"

class Lake : public GameField
{
public:
    Lake(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};
    ~Lake() {}

    bool inline IsLake() const override { return true; }
};

#endif