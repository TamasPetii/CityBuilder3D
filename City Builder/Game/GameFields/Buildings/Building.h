#ifndef BUILDING_H
#define BUILDING_H

#include <sstream>
#include "../GameField.h"

class Building : public GameField
{
public:
    Building(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Building() {}

    static std::string ToString(Building* building);

    bool inline IsBuilding() const override { return true; }
    virtual inline bool IsPoliceStation() const { return false; }
    virtual inline bool IsFireStation() const { return false; }
    virtual inline bool IsPowerWire() const { return false; }
    virtual inline bool IsPowerStation() const { return false; }
    virtual inline bool IsSchool() const { return false; }
    virtual inline bool IsStadium() const { return false; }
    virtual inline float GetBuildingSatisfaction() const { return 0; }
};

#endif