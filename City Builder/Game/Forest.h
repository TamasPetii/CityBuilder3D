#ifndef FOREST_H
#define FOREST_H

#include "GameField.h"

class Forest : public GameField
{
public:
    Forest() : GameField() {};
    ~Forest() {}

    bool inline IsForest() const override { return true; }
};

#endif