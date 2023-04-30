#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include "GameFields/_GameFieldHeaders.h"
#include <cmath>

struct Point {
	int x, y;
	bool isInterSection;
};

class GameTable
{
public:
	GameTable(int TableSize);
	~GameTable() = default;

	bool ValidateCoordinate(int c);
	bool ValidateCoordinate(int c1, int c2);
	bool IsBuildableField(int x, int y);
	bool IsBuildable(FieldType type, FieldDirection dir, int x, int y);

	//Setter
	void Set_TableValue(int x, int y, FieldType type);// TODO: Delete previous field (We are using heap to store objects -> need to delete)
	void Set_TableValue(int x, int y, GameField* field);

	//Getter
	inline int Get_TableSize() const { return m_TableSize; }
	inline GameField* Get_TableValue(int x, int y) const { return m_Table[x][y]; }; //Todo: check for wrong x,y value
	ZoneDetails Get_ZoneDetails(int x, int y) const { ZoneDetails s;  return s; };
	float Get_TotalCost() const;

	std::vector<Point> PathFinder(Point start, Point end);
	bool IsInterSection(Point p);
	bool recalculate = false;

	void Loop();

	static bool changed;
private:
	std::vector<std::vector<GameField*>> m_Table;
	int m_TableSize;
	void SetRoadNetwork(int x, int y);
	void SetBuildingNetwork(int x, int y);
	void SetZoneNetwork(int x, int y);
	void RebuildRoadNetwork();

	template<typename Function>
	void LoopThroughNeighbors(int, int, Function);
	void AddIndustrialAreaBonus(GameField*, int);
	void CheckZoneIndustrialBonus(GameField*);
	void DeleteField(int, int, FieldType);
	static float distance(GameField*, GameField*);


	void SimulateFire(GameField*);
};
