#include "GameTable.h"
#include "RoadNetwork.h"
#include <stdio.h>

GameTable::GameTable(int TableSize) : m_TableSize(TableSize)
{
	//Todo: check for wrong tablesize value
	m_Table.resize(m_TableSize);

	for (int i = 0; i < m_TableSize; i++)
	{
		m_Table[i].resize(m_TableSize);

		for (int j = 0; j < m_TableSize; j++)
		{
			m_Table[i][j] = GameField::CreateField(EMPTY, i, j);
		}
	}
}

void GameTable::Set_TableValue(int x, int y, FieldType type)
{
	bool isRoad = dynamic_cast<Road*>(m_Table[x][y]);
	bool isDelete = false;
	if (!m_Table[x][y]->IsEmpty()) {
		if (!(type == EMPTY || type == CRATER)) return;
		if (!isRoad)
		{
			if (m_Table[x][y]->IsZone())
			{
				Zone* zone = dynamic_cast<Zone*>(m_Table[x][y]);
				zone->DeleteZone();
			}

			RoadNetwork::RemoveFromNetwork(m_Table[x][y]);
		}
		delete(m_Table[x][y]);
		isDelete = true;
	}

	m_Table[x][y] = GameField::CreateField(type, x, y);

	GameField* newField = m_Table[x][y];
	if (isRoad && isDelete) RebuildRoadNetwork();

	if (type == ROAD) {
		SetRoadNetwork(x, y);
	}
	else if (!(type == EMPTY || type == FOREST || type == POWERWIRE || type == POWERSTATION)) {
		SetBuildingNetwork(x, y);
		//TODO: megnézni, hogy van -e a környezetben közvetlen rálátású erdõ,
		//illetve hogy blokkoltuk -e valakinek a rálátását.
	}
	else if (type == FOREST) {
		//TODO: növelni a szomszédos mezõk elégedettségét, ha rálátnak az erdõre
	}
}

float GameTable::Get_TotalCost() const
{
	float totalCost = 0.0f;

	for (int i = 0; i < m_TableSize; ++i) {
		for (int j = 0; j < m_TableSize; ++j) {
			totalCost += m_Table[i][j]->Get_Cost();
		}
	}

	return totalCost;
}

void GameTable::SetRoadNetwork(int x, int y) {
	GameField* newRoad = m_Table[x][y];
	for (int i = -1; i < 2; i += 1) {
		for (int j = -1; j < 2; j += 1) {
			if ((abs(i) + abs(j)) == 2) continue;
			if (i == 0 && j == 0) continue; //végigmegyünk a szomszédokon
			if (x + i < 0 || x + i >= m_TableSize || y + j < 0 || y + j > m_TableSize) continue;
			GameField* adj = m_Table[x + i][y + j];
			if (Road* road = dynamic_cast<Road*>(adj)) {
				int id = RoadNetwork::GetNetworkId(adj);
				if (RoadNetwork::GetNetworkId(newRoad) == -1) {
					RoadNetwork::AddToNetwork(newRoad, id);
				}
				else {
					if (RoadNetwork::GetNetworkId(newRoad) != id) {
						RoadNetwork::MergeNetworks(id, RoadNetwork::GetNetworkId(newRoad));
					}
				}
			}
		}
	}

	if (RoadNetwork::GetNetworkId(newRoad) == -1) {
		RoadNetwork::AddToNetwork(newRoad, RoadNetwork::CreateNetwork());
	}

	for (int i = -1; i < 2; i += 1) {
		for (int j = -1; j < 2; j += 1) {
			if ((abs(i) + abs(j)) == 2) continue;
			if (i == 0 && j == 0) continue;
			if (x + i < 0 || x + i >= m_TableSize || y + j < 0 || y + j > m_TableSize) continue;
			GameField* adj = m_Table[x + i][y + j];
			if (!(dynamic_cast<Forest*>(adj) || dynamic_cast<Empty*>(adj)
				|| dynamic_cast<PowerWire*>(adj) || dynamic_cast<PowerStation*>(adj) || dynamic_cast<Road*>(adj) )) {
				std::cout << "Add building to new network! " << std::endl;
				RoadNetwork::AddToNetwork(adj, RoadNetwork::GetNetworkId(newRoad));
			}
		}
	}
}

void GameTable::SetBuildingNetwork(int x, int y) {
	GameField* newBuilding = m_Table[x][y];
	for (int i = -1; i < 2; i += 1) {
		for (int j = -1; j < 2; j += 1) {
			if ((abs(i) + abs(j)) == 2) continue;
			if (i == 0 && j == 0) continue;
			if (x + i < 0 || x + i >= m_TableSize || y + j < 0 || y + j >= m_TableSize) continue;
			GameField* adj = m_Table[x + i][y + j];
			if (Road* road = dynamic_cast<Road*>(adj)) {
				int id = RoadNetwork::GetNetworkId(adj);
				RoadNetwork::AddToNetwork(newBuilding, id);
			}
		}
	}
}

void GameTable::RebuildRoadNetwork() {
	RoadNetwork::ResetNetworks();
	for (int i = 0; i < m_TableSize; i++) {
		for (int j = 0; j < m_TableSize; j++) {
			GameField* tile = m_Table[i][j];
			if (dynamic_cast<Road*>(tile)) {
				SetRoadNetwork(i, j);
			}
			if (!(dynamic_cast<Forest*>(tile) || dynamic_cast<Empty*>(tile)
				|| dynamic_cast<PowerWire*>(tile) || dynamic_cast<PowerStation*>(tile) || dynamic_cast<Road*>(tile))) {
				SetBuildingNetwork(i, j);
			}
		}
	}
}


std::vector<Point> GameTable::PathFinder(Point start, Point end)
{
	//directions
	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	//initialize visited matrix
	std::vector<std::vector<bool>> visited(m_TableSize, std::vector<bool>(m_TableSize, false));

	//queue and path for BFS
	std::queue<Point> q;
	std::vector<std::vector<Point>> path(m_TableSize, std::vector<Point>(m_TableSize)); //for every point we store where it is reachable from

	q.push(start);
	path[start.x][start.y] = start;

	//start
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; i++)
		{
			Point curr = q.front();
			q.pop();

			for (int k = 0; k < 4; k++)
			{
				if (curr.x + dx[k] == end.x && curr.y + dy[k] == end.y)
				{
					std::vector<Point> shortestPath;
					Point p = { curr.x, curr.y };
					while (p.x != start.x || p.y != start.y)
					{
						shortestPath.push_back(p); //p is added to the shortes path
						p = path[p.x][p.y]; //p will be the point from which we previously reached (the previous) p
					}
					shortestPath.push_back(start);
					reverse(shortestPath.begin(), shortestPath.end());

					for (int i = 0; i < shortestPath.size(); i++)
					{
						std::cout << shortestPath[i].x << "," << 0 << "," << shortestPath[i].y << std::endl;
					}
					std::cout << std::endl;
					return shortestPath;
				}
			}

			//mark current point as visited
			visited[curr.x][curr.y] = true;

			//explore the neighbors
			for (int j = 0; j < 4; j++)
			{
				int nx = curr.x + dx[j];
				int ny = curr.y + dy[j];
				if (nx >= 0 && nx < m_TableSize && ny >= 0 && ny < m_TableSize && m_Table[nx][ny]->IsRoad() && !visited[nx][ny])
				{
					Point p = { nx, ny };
					q.push(p);
					visited[nx][ny] = true;
					path[nx][ny] = curr; //the neighbours origin will be the current point
				}
			}
		}
	}

	//end point is unreachable
	return {};
}