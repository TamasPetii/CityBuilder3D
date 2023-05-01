#pragma once
#include <string>
#include "GameFieldLayout.h"

class GameField
{
public:
	GameField(FieldType type, FieldDirection direction, int x, int y);
	~GameField() {}

	//Static Methodes
	static GameField* CreateField(FieldType type, FieldDirection direction, int x, int y);
	static std::string ConvertTypeToStr(FieldType type);
	static int CalculateBuildCost(FieldType type);
	static int CalculateAnnualCost(FieldType type);
	static std::string ToString(GameField* field);

	//Identification Methodes
	virtual bool IsCrater()   const { return false; }
	virtual bool IsZone()     const { return false; }
	virtual bool IsEmpty()    const { return false; }
	virtual bool IsRoad()     const { return false; }
	virtual bool IsForest()   const { return false; }
	virtual bool IsLake()     const { return false; }
	virtual bool IsBuilding() const { return false; }

	//Getter Methodes
	inline int Get_X() const { return m_X; }
	inline int Get_Y() const { return m_Y; }
	inline int Get_BuildCost() const { return m_BuildCost; }
	inline int Get_AnnualCost() const { return m_AnnualCost; }
	inline float Get_SatisfactionPoints() const { return m_SatisfactionPoints; }
	inline FieldType Get_Type() const { return m_Type; }
	inline FieldDirection Get_Direction() const { return m_Direction; }

	//Setter Methodes
	inline void Set_X(int X) { m_X = X; }
	inline void Set_Y(int Y) { m_Y = Y; }
	inline void Set_BuildCost(int BuildCost) { m_BuildCost = BuildCost; }
	inline void Set_AnnualCost(int AnnualCost) { m_AnnualCost = AnnualCost; }
	inline void Set_SatisfactionPoints(float SatisfactionPoints) { m_SatisfactionPoints = SatisfactionPoints; }
	inline void Set_Type(FieldType Type) { m_Type = Type; }
	inline void Set_Direction(FieldDirection Direction) { m_Direction = Direction; }

protected:
	int m_X;
	int m_Y;
	int m_BuildCost;
	int m_AnnualCost;
	float m_SatisfactionPoints;
	FieldType m_Type;
	FieldDirection m_Direction;
};