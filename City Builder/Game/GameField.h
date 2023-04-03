#pragma once

enum FieldType
{
	RESIDENTIAL_LVL1,
	RESIDENTIAL_LVL2,
	RESIDENTIAL_LVL3,
	INDUSTRIAL_LVL1,
	INDUSTRIAL_LVL2,
	INDUSTRIAL_LVL3,
	SERVICE_LVL1,
	SERVICE_LVL2,
	SERVICE_LVL3,
	EMPTY,
	ROAD,
	FOREST,
	POLICESTATION,
	FIRESTATION,
	HIGHSCHOOL,
	UNIVERSITY,
	STADIUM,
	POWERSTATION,
	POWERWIRE
};

class GameField
{
public:
	GameField() {}
	~GameField() {}

	GameField CreateField(FieldType type);

	virtual bool IsZone() const;
	virtual bool IsEmpty() const;
	virtual bool IsRoad() const;
	virtual bool IsForest() const;
	virtual bool IsBuilding() const;

	float Get_SatisfactionPoints() const;
	float Get_Fee() const;
	float Get_Cost() const;

private:
	int m_Cost;
	int m_Fee;
	float m_SatisfactionPoints;
	float m_Power;
};
