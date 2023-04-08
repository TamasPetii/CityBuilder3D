#pragma once

#include <iostream>
#include <vector>

#include "GameFields/_GameFieldHeaders.h"

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

	void UpgradeField(int x, int y) {};

private:
	std::vector<std::vector<GameField*>> m_Table;
	int m_TableSize;
	void SetRoadNetwork(int x, int y);
	void SetBuildingNetwork(int x, int y);
	void RebuildRoadNetwork();
};
