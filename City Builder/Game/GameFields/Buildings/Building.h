#ifndef BUILDING_H
#define BUILDING_H

#include "../GameField.h"

class Building : public GameField
{
protected:
    Building(FieldType type, int x, int y, float cost) : GameField(type, x, y, cost) {};

public:
    ~Building() {}

    bool inline IsBuilding() const override { return true; }
    virtual inline bool IsPoliceStation() const { return false; }
    virtual inline bool IsFireStation() const { return false; }
    virtual inline bool IsPowerWire() const { return false; }
    virtual inline bool IsPowerStation() const { return false; }
    virtual inline bool IsSchool() const { return false; }
    virtual inline bool IsStadium() const { return false; }
};

#endif