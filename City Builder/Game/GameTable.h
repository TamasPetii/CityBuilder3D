#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "GameFields/_GameFieldHeaders.h"

struct Point {
	int x, y;
	bool isInterSection;
};

class GameTable
{
public:
	GameTable(int TableSize);
	~GameTable() = default;

	//Setter
	void Set_TableValue(int x, int y, FieldType type);// TODO: Delete previous field (We are using heap to store objects -> need to delete)
	
	//Getter
	inline int Get_TableSize() const { return m_TableSize; }
	inline GameField* Get_TableValue(int x, int y) const { return m_Table[x][y]; }; //Todo: check for wrong x,y value
	ZoneDetails Get_ZoneDetails(int x, int y) const { ZoneDetails s;  return s; };
	float Get_TotalCost() const;

	void UpgradeField(int x, int y) {};
	std::vector<Point> PathFinder(Point start, Point end);
	bool IsInterSection(Point p);

private:
	std::vector<std::vector<GameField*>> m_Table;
	int m_TableSize;
	void SetRoadNetwork(int x, int y);
	void SetBuildingNetwork(int x, int y);
	void RebuildRoadNetwork();
};