#ifndef EMPTY_H
#define EMPTY_H

#include "../GameField.h"

class Empty : public GameField
{
public:
    Empty(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};
    ~Empty() {}

    bool inline IsEmpty() const override { return true; }
};

#endif

