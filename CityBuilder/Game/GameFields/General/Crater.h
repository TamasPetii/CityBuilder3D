#ifndef CRATER_H
#define CRATER_H

#include "../GameField.h"

class Crater : public GameField
{
public:
    Crater(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Crater() {}

    bool inline IsCrater() const override { return true; }
};

#endif

