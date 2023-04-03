#ifndef EMPTY_H
#define EMPTY_H

#include "GameField.h"

class Empty : public GameField
{
public:
    Empty() : GameField() {};
    ~Empty() {}

    bool inline IsEmpty() const override { return true; }
};

#endif

