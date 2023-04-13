#ifndef EMPTY_H
#define EMPTY_H

#include "../GameField.h"

class Empty : public GameField
{
public:
    Empty(float cost) : GameField(cost) {};
    ~Empty() {}

    bool inline IsEmpty() const override { return true; }
};

#endif

