#ifndef FOREST_H
#define FOREST_H

#include "../GameField.h"

class Forest : public GameField
{
public:
    Forest(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Forest() {}

    bool inline IsForest() const override { return true; }

    int age = 9;
};

#endif