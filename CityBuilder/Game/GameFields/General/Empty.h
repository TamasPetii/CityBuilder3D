#ifndef EMPTY_H
#define EMPTY_H

#include "../GameField.h"

class Empty : public GameField
{
public:
    Empty(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Empty() {}

    bool inline IsEmpty() const override { return true; }
};

#endif

