#pragma once

#include "GameFieldType.h"

class GameField
{
public:
	GameField(float cost): m_Cost(cost) {}
	~GameField() {}

	static GameField* CreateField(FieldType type);

	virtual bool IsZone() const { return false; };
	virtual bool IsEmpty() const { return false; };
	virtual bool IsRoad() const { return false; };
	virtual bool IsForest() const { return false; };
	virtual bool IsBuilding() const { return false; };

	float Get_SatisfactionPoints() const;
	float Get_Fee() const;
	float Get_Cost() const;

private:
	int m_Fee;
	float m_Cost;
	float m_SatisfactionPoints;
	float m_Power;
};
