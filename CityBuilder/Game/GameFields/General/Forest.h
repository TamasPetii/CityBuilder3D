#ifndef FOREST_H
#define FOREST_H

#include "../GameField.h"

class Forest : public GameField
{
public:
    Forest(FieldType type, FieldDirection direction, int x, int y) : GameField(type, direction, x, y) {};
    ~Forest() {}

    inline bool IsForest() const override { return true; }
    inline int  Get_Age() const { return m_Age; }
    inline void Set_Age(int age) { m_Age = age; }
    inline void Increase_Age() { ++m_Age; }
    inline float Get_SatisfactionPoints() { return m_Booster * m_Age; }

private:
    float m_Booster = 0.025f;
    int m_Age = 0;
};

#endif