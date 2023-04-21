#ifndef FOREST_H
#define FOREST_H

#include "../GameField.h"

class Forest : public GameField
{
public:
    Forest(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};
    ~Forest() {}

    bool inline IsForest() const override { return true; }

    int age = 9;
};

#endif