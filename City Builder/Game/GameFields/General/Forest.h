#ifndef FOREST_H
#define FOREST_H

#include "../GameField.h"

class Forest : public GameField
{
public:
    Forest(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Forest() {}

    bool inline IsForest() const override { return true; }
    int inline Get_Age() const { return m_Age; }
    void inline Set_Age(int age) { m_Age = age; }
    void inline Increase_Age() { ++m_Age; }
    void inline Increase_SatisfactionPoints() { m_SatisfactionPoints += 0.5; }
    void inline Set_Cost(float cost) { m_Cost = cost; }

private:
    int m_Age = 0;
};

#endif