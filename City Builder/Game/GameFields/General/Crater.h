#ifndef CRATER_H
#define CRATER_H

#include "../GameField.h"

class Crater : public GameField
{
public:
    Crater(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};
    ~Crater() {}

    bool inline IsCrater() const override { return true; }
};

#endif

