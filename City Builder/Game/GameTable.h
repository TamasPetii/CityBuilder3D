#pragma once

#include <iostream>
#include <vector>

class GameTable
{
public:
	GameTable(int TableSize);

	//Setter
	void Set_TableValue(int x, int y, int value) { m_Table[x][y] = value; }
	//Getter
	inline int Get_TableSize() const { return m_TableSize; }
	inline int Get_TableValue(int x, int y) const { return m_Table[x][y]; }; //Todo: check for wrong x,y value
private:
	std::vector<std::vector<int>> m_Table;
	int m_TableSize;
};