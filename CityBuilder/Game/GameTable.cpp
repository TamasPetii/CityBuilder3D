#include "GameTable.h"
#include "RoadNetwork.h"

bool GameTable::CHANGED = false;

/**
 * Constructs a GameTable object with a given table size.
 *
 * @param TableSize The size of the table.
 *
 * @returns None
 */
GameTable::GameTable(int TableSize) : m_TableSize(TableSize)
{
	m_Table.resize(m_TableSize);

	for (int i = 0; i < m_TableSize; i++)
	{
		m_Table[i].resize(m_TableSize);

		for (int j = 0; j < m_TableSize; j++)
		{
			m_Table[i][j] = GameField::CreateField(EMPTY, FRONT, i, j);
		}
	}
}

/**
 * Sets the value of a GameField object in the GameTable at the specified coordinates.
 *
 * @param x The x-coordinate of the GameField object in the GameTable.
 * @param y The y-coordinate of the GameField object in the GameTable.
 * @param field A pointer to the GameField object to be set in the GameTable.
 *
 * @returns None
 */
void GameTable::Set_TableValue(int x, int y, GameField* field)
{
	delete m_Table[x][y];
	m_Table[x][y] = field;
	SetBuildingNetwork(x, y);
}

/**
 * Sets the value of a field in the game table.
 *
 * @param x The x-coordinate of the field.
 * @param y The y-coordinate of the field.
 * @param type The type of the field.
 * @param direction The direction of the field.
 *
 * @returns None
 */
void GameTable::Set_TableValue(int x, int y, FieldType type, FieldDirection direction) {
	if (!m_Table[x][y]->IsEmpty()) { //t�rl�s
		if (!(type == EMPTY || type == CRATER)) return;
		DeleteField(x, y, type);
		return;
	}
	else {
		m_Table[x][y] = GameField::CreateField(type, direction, x, y);
	}

	if (type == ROAD) {
		SetRoadNetwork(x, y);
	}
	else if (!(type == EMPTY || type == FOREST || type == POWERWIRE)) {
		if (Zone* zone = dynamic_cast<Zone*>(m_Table[x][y])) {
			SetZoneNetwork(x, y);
			if (zone->IsWorkingArea()) {
				if (WorkingArea* w = dynamic_cast<WorkingArea*>(zone)) {
					if (w->IsIndustrialArea()) AddIndustrialAreaBonus(w, 1);
				}
			}
			else if (zone->IsResidentalArea()) {
				CheckZoneIndustrialBonus(zone);
			}
		}
		else {
			SetBuildingNetwork(x, y);
		}
		//TODO: megn�zni, hogy van -e a k�rnyezetben k�zvetlen r�l�t�s� erd�,
		//illetve hogy blokkoltuk -e valakinek a r�l�t�s�t.
	}
	else if (type == FOREST) {
		//TODO: n�velni a szomsz�dos mez�k el�gedetts�g�t, ha r�l�tnak az erd�re
	}
}

/**
 * Deletes a field from the game table and updates the game state accordingly.
 *
 * @param x The x-coordinate of the field to be deleted.
 * @param y The y-coordinate of the field to be deleted.
 * @param type The type of the field to be created in place of the deleted field.
 *
 * @returns None
 */
void GameTable::DeleteField(int x, int y, FieldType type) {
	if (m_Table[x][y]->Get_Type() == LAKE) return;

	bool isRoad = dynamic_cast<Road*>(m_Table[x][y]);
	bool isIndustrial = false;
	bool type_big = m_Table[x][y]->Get_Type() == STADIUM || m_Table[x][y]->Get_Type() == UNIVERSITY || m_Table[x][y]->Get_Type() == POWERSTATION || m_Table[x][y]->Get_Type() == HIGHSCHOOL;
	if (!isRoad) {
		if (m_Table[x][y]->IsZone())
		{
			Zone* zone = dynamic_cast<Zone*>(m_Table[x][y]);
			if (WorkingArea* w = dynamic_cast<WorkingArea*>(zone)) {
				if (w->IsIndustrialArea()) {
					AddIndustrialAreaBonus(w, -1);
					isIndustrial = true;
				}
			}
			zone->DeleteZone();
		}
		if (type_big)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int new_x = x + i;
					int new_y = y + j;
					if (ValidateCoordinate(new_x, new_y) && !(i == 0 && j == 0) && m_Table[x][y] == m_Table[new_x][new_y])
					{
						RoadNetwork::RemoveFromNetwork(m_Table[new_x][new_y]);
						m_Table[new_x][new_y] = GameField::CreateField(type, FRONT, new_x, new_y);
					}
				}
			}
		}

		RoadNetwork::RemoveFromNetwork(m_Table[x][y]);
	}
	delete(m_Table[x][y]);

	m_Table[x][y] = GameField::CreateField(type, FRONT, x, y);
	GameField* newField = m_Table[x][y];

	if (isRoad) RebuildRoadNetwork();
}

// Calculate the total annual cost of all fields in the game table.
int GameTable::Get_TotalAnnualCost() const
{
	int totalCost = 0;

	for (int i = 0; i < m_TableSize; ++i) {
		for (int j = 0; j < m_TableSize; ++j) {
			totalCost += m_Table[i][j]->Get_AnnualCost();
		}
	}

	return totalCost;
}

/**
 * Sets the road network for a given GameField.
 *
 * @param x The x-coordinate of the GameField.
 * @param y The y-coordinate of the GameField.
 *
 * @returns None
 */
void GameTable::SetRoadNetwork(int x, int y) {
	GameField* newRoad = m_Table[x][y];
	//Magyar�zat: a []-ben adjuk meg, hogy mit szeretn�nk a lambd�ban haszn�lni(capture list)
	//az adj pedig az �ppen sorraker�l� szomsz�d
	LoopThroughNeighbors(x, y, [this, newRoad](GameField* adj) {
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
	});

	if (RoadNetwork::GetNetworkId(newRoad) == -1) {
		RoadNetwork::AddToNetwork(newRoad, RoadNetwork::CreateNetwork());
	}

	LoopThroughNeighbors(x, y, [this, newRoad](GameField* adj) {
		if (!(dynamic_cast<Forest*>(adj) || dynamic_cast<Empty*>(adj)
			|| dynamic_cast<PowerWire*>(adj) || dynamic_cast<Road*>(adj))) {
			int id = RoadNetwork::GetNetworkId(newRoad);

			bool added = RoadNetwork::AddToNetwork(adj, id);
			if (!added) return;
			if (dynamic_cast<Zone*>(adj)) {
				RoadNetwork::SetZoneSatisfaction(adj);
			}
			else {
				RoadNetwork::AddToNetworkSatisfaction(adj, id);
			}	
		}
	});
}

/**
 * Sets the building network for a given location on the game table.
 *
 * @param x The x-coordinate of the location.
 * @param y The y-coordinate of the location.
 *
 * @returns None
 */
void GameTable::SetBuildingNetwork(int x, int y) {
	GameField* newBuilding = m_Table[x][y];
	LoopThroughNeighbors(x, y, [this, newBuilding](GameField* adj) {
		if (Road* road = dynamic_cast<Road*>(adj)) {
			int id = RoadNetwork::GetNetworkId(adj);
			bool added = RoadNetwork::AddToNetwork(newBuilding, id);
			//ha added, teh�t m�g nem volt benne a networkben, akkor sz�moljuk az el�gedetts�get is
			if (added) RoadNetwork::AddToNetworkSatisfaction(newBuilding, id);
		}
	});
}

/**
 * Sets the network of a zone based on its neighbors.
 *
 * @param x The x-coordinate of the zone.
 * @param y The y-coordinate of the zone.
 *
 * @returns None
 */
void GameTable::SetZoneNetwork(int x, int y) {
	GameField* newZone = m_Table[x][y];
	LoopThroughNeighbors(x, y, [this, newZone](GameField* adj) {
		if (Road* road = dynamic_cast<Road*>(adj)) {
			int id = RoadNetwork::GetNetworkId(adj);
			bool added = RoadNetwork::AddToNetwork(newZone, id);
			if (added) RoadNetwork::SetZoneSatisfaction(newZone); 
		}
	});
}

/**
 * Rebuilds the road network of the game table.
 *
 * @returns None
 */
void GameTable::RebuildRoadNetwork() {
	RoadNetwork::ResetNetworks();

	for (int i = 0; i < m_TableSize; i++) {
		for (int j = 0; j < m_TableSize; j++) {
			GameField* tile = m_Table[i][j];
			if (Zone* zone = dynamic_cast<Zone*>(tile)) {
				zone->Set_IndustrialPenalty(0);
				zone->Set_Safety(0);
				zone->Set_Satisfaction(0);
			}
		}
	}


	for (int i = 0; i < m_TableSize; i++) {
		for (int j = 0; j < m_TableSize; j++) {
			GameField* tile = m_Table[i][j];
			if (dynamic_cast<Road*>(tile)) {
				SetRoadNetwork(i, j);
			}
			else if (dynamic_cast<Zone*>(tile)) {
				Zone* zone = dynamic_cast<Zone*>(tile);
				SetZoneNetwork(i, j);
				if (zone->IsWorkingArea()) {
					if (WorkingArea* w = dynamic_cast<WorkingArea*>(zone)) {
						if (w->IsIndustrialArea()) AddIndustrialAreaBonus(w, 1);
					}
				}
			}
			else if (Building* b = dynamic_cast<Building*>(tile)) {
				if (!b->IsPowerWire()) SetBuildingNetwork(i, j);
			}
		}
	}
	recalculate = true;
}

/**
 * Loops through the neighbors of a cell in the game table and applies a given function to each neighbor.
 *
 * @tparam Function The type of the function to apply to each neighbor.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param func The function to apply to each neighbor.
 *
 * @returns None
 */
template<typename Function>
void GameTable::LoopThroughNeighbors(int x, int y, Function func) {
	for (int i = -1; i < 2; i += 1) {
		for (int j = -1; j < 2; j += 1) {
			if ((abs(i) + abs(j)) == 2) continue;
			if (i == 0 && j == 0) continue;
			if (x + i < 0 || x + i >= m_TableSize || y + j < 0 || y + j >= m_TableSize) continue;
			func(m_Table[x + i][y + j]);
		}
	}
}

/**
 * Computes the Euclidean distance between two GameFields.
 *
 * @param g1 A pointer to the first GameField.
 * @param g2 A pointer to the second GameField.
 *
 * @returns The Euclidean distance between the two GameFields.
 */
float GameTable::distance(GameField* g1, GameField* g2) {
	return (float)sqrt(pow(g1->Get_X() - g2->Get_X(), 2) + pow(g1->Get_Y() - g2->Get_Y(), 2));
}

/**
 * Adds an industrial area bonus to the game field.
 *
 * @param f A pointer to the game field.
 * @param placed The number of industrial areas placed.
 *
 * @returns None
 */
void GameTable::AddIndustrialAreaBonus(GameField* f, int placed) {
	for (int i = -9; i <= 9; i++) {
		for (int j = -9; j <= 9; j++) {
			if (f->Get_X() + i < 0 || f->Get_X() + i >= m_TableSize || f->Get_Y() + j < 0 || f->Get_Y() + j >= m_TableSize) continue;
			if (Zone* zone = dynamic_cast<Zone*>(m_Table[f->Get_X() + i][f->Get_Y() + j])) {
				if (zone->IsResidentalArea()) {
					int d = (int)distance(f, zone);
					float penalty = (10 - d) / 10.0f;
					//placed 1, ha lerak, -1, ha t�r�l
					zone->Add_IndustrialPenalty(placed * -1 * penalty);
				}
			}

		}
	}
}

/**
 * Checks if a residential zone is within range of an industrial zone and applies an industrial penalty to the residential zone if so.
 *
 * @param f A pointer to the game field to check.
 *
 * @returns None
 */
void GameTable::CheckZoneIndustrialBonus(GameField* f) {
	Zone* residentialZone = dynamic_cast<Zone*>(f);
	for (int i = -9; i <= 9; i++) {
		for (int j = -9; j <= 9; j++) {
			if (f->Get_X() + i < 0 || f->Get_X() + i >= m_TableSize || f->Get_Y() + j < 0 || f->Get_Y() + j >= m_TableSize) continue;
			if (Zone* zone = dynamic_cast<Zone*>(m_Table[f->Get_X() + i][f->Get_Y() + j])) {
				if (WorkingArea* w = dynamic_cast<WorkingArea*>(zone)) {
					if (w->IsIndustrialArea()) {
						int d = (int)distance(w, f);
						if (d < 10) {
							float penalty = (10 - d) / 10.0;
							residentialZone->Add_IndustrialPenalty(-1 * penalty);
						}
					}
				}
			}

		}
	}
}

/**
 * Validates if a given coordinate is within the bounds of the game table.
 *
 * @param c The coordinate to be validated.
 *
 * @returns True if the coordinate is valid, False otherwise.
 */
bool GameTable::ValidateCoordinate(int c)
{
	return c >= 0 && c < m_Table.size();
}

/**
 * Validates whether the given coordinates are within the bounds of the game table.
 *
 * @param c1 The first coordinate to validate.
 * @param c2 The second coordinate to validate.
 *
 * @returns True if both coordinates are within the bounds of the game table, false otherwise.
 */
bool GameTable::ValidateCoordinate(int c1, int c2)
{
	return ValidateCoordinate(c1) && ValidateCoordinate(c2);
}

/**
 * Checks if a field on the game table is buildable.
 *
 * @param x The x-coordinate of the field.
 * @param y The y-coordinate of the field.
 *
 * @returns True if the field is buildable, false otherwise.
 */
bool GameTable::IsBuildableField(int x, int y)
{
	return ValidateCoordinate(x, y) && m_Table[x][y]->IsEmpty();
}

/**
 * Determines if a field is buildable based on the type of building, direction, and location.
 *
 * @param type The type of building to be constructed.
 * @param dir The direction in which the building will be constructed.
 * @param x The x-coordinate of the location where the building will be constructed.
 * @param y The y-coordinate of the location where the building will be constructed.
 *
 * @returns True if the field is buildable, false otherwise.
 */
bool GameTable::IsBuildable(FieldType type, FieldDirection dir, int x, int y)
{
	if (type == STADIUM || type == POWERSTATION || type == UNIVERSITY)
	{
		if (!IsBuildableField(x, y)) return false;
		if (!IsBuildableField(x + 1, y)) return false;
		if (!IsBuildableField(x, y + 1)) return false;
		if (!IsBuildableField(x + 1, y + 1)) return false;
	}
	else if (type == HIGHSCHOOL)
	{
		if (!IsBuildableField(x, y)) return false;

		if (dir == FRONT || dir == BACK)
		{
			if (!IsBuildableField(x, y + 1)) return false;
		}

		if (dir == LEFT || dir == RIGHT)
		{
			if (!IsBuildableField(x + 1, y)) return false;
		}
	}
	else
	{
		if (!IsBuildableField(x, y)) return false;
	}

	return true;
}

/**
 * Simulates a fire on a given game field.
 *
 * @param field A pointer to the game field to simulate the fire on.
 *
 * @returns None
 */
void GameTable::SimulateFire(GameField* field)
{
	//Fire appears randomly
	if ((field->IsZone() || field->IsBuilding()) && field->Get_Type() != FIRESTATION)
	{
		field->RandomFire();
		CHANGED = CHANGED || field->OnFire();
	}

	//Updateing fire state + Fire spread
	if (field->OnFire())
	{
		field->FireCounter--;
		//Spread
		if (field->FireCounter == 250)
		{
			//Loop through the neighbours and set them fire :)
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int nbX = x + field->Get_X();
					int nbY = y + field->Get_Y();
					if (!ValidateCoordinate(nbX, nbY)) continue;

					bool type = (m_Table[nbX][nbY]->IsZone() || m_Table[nbX][nbY]->IsBuilding()) && m_Table[nbX][nbY]->Get_Type() != FIRESTATION;

					if (type && !m_Table[nbX][nbY]->OnFire())
					{
						bool fire = (rand() % 3 == 0);
						m_Table[nbX][nbY]->OnFire() = fire;

						CHANGED = CHANGED || fire;
					}
				}
			}
		}
	}

	if (field->FireCounter == 0)
	{
		this->Set_TableValue(field->Get_X(), field->Get_Y(), EMPTY, FRONT);
		CHANGED = true;
	}
}

/**
 * Simulates fire spreading on the game table by iterating over each cell and calling the SimulateFire function.
 *
 * @returns None
 */
void GameTable::Loop()
{
	for (int x = 0; x < m_Table.size(); x++)
	{
		for (int y = 0; y < m_Table.size(); y++)
		{
			SimulateFire(m_Table[x][y]);
		}
	}
}

/**
 * Determines if a given point on the game table is an intersection.
 *
 * @param p The point to check.
 *
 * @returns True if the point is an intersection, false otherwise.
 */
bool GameTable::IsInterSection(Point p)
{
	if (m_Table[p.x][p.y]->IsRoad())
	{
		int dx[] = { -1, 0, 1, 0 };
		int dy[] = { 0, 1, 0, -1 };

		int numberOfNeighbourRoads = 0;

		for (int i = 0; i < 4; ++i)
		{
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];

			if (nx >= 0 && nx < m_TableSize && ny >= 0 && ny < m_TableSize)
			{
				if (m_Table[nx][ny]->IsRoad())
				{
					++numberOfNeighbourRoads;
				}
			}
		}
		return numberOfNeighbourRoads > 2;
	}
	else
	{
		return false;
	}
}

//BFS based algorithm that finds the shortest path between a starting point and an end point
//start point should be a road field
//the algorithm returns the vector of points (coordinates of road fields) when the end point is one of it's neighbours
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

	//check if start is an intersection
	start.isInterSection = IsInterSection(start);

	q.push(start);
	path[start.x][start.y] = start;

	//start
	while (!q.empty())
	{
		int size = (int)q.size();
		for (int i = 0; i < size; i++)
		{
			Point curr = q.front();
			q.pop();

			for (int k = 0; k < 4; k++)
			{
				if (curr.x + dx[k] == end.x && curr.y + dy[k] == end.y)
				{
					std::vector<Point> shortestPath;
					Point p = { curr.x, curr.y, IsInterSection({curr.x,curr.y}) };

					while (p.x != start.x || p.y != start.y)
					{
						shortestPath.push_back(p); //p is added to the shortes path
						p = path[p.x][p.y]; //p will be the point from which we previously reached (the previous) p
					}
					shortestPath.push_back(start);
					std::reverse(shortestPath.begin(), shortestPath.end());

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
					Point p = { nx, ny, IsInterSection({nx, ny}) };
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

//BFS based algorithm to find the fields that are on fire from a starting point (the field that is on fire is accessible via road fields�
std::unordered_set<int> GameTable::PathFinder_Fire(Point start)
{
	//directions
	int dx[] = { -1, 0, 1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	//initialize visited matrix
	std::vector<std::vector<bool>> visited(m_TableSize, std::vector<bool>(m_TableSize, false));

	//queue and path for BFS
	std::queue<Point> q;
	std::unordered_set<int> fieldsOnFire;

	for (int i = 0; i < 4; ++i)
	{
		int x = start.x + dx[i];
		int y = start.y + dy[i];

		if (ValidateCoordinate(x,y) && Get_TableValue(x,y)->IsRoad())
		{
			q.push({x, y});
		}
	}

	//start
	while (!q.empty())
	{
		int size = (int)q.size();
		for (int i = 0; i < size; i++)
		{
			Point curr = q.front();
			q.pop();

			for (int k = 0; k < 4; k++)
			{
				int x = curr.x + dx[k];
				int y = curr.y + dy[k];

				if (ValidateCoordinate(x, y) && Get_TableValue(x,y)->OnFire())
				{
					fieldsOnFire.insert(x * m_TableSize + y);
				}
			}

			//mark current point as visited
			visited[curr.x][curr.y] = true;

			//explore the neighbors
			for (int j = 0; j < 4; j++)
			{
				int nx = curr.x + dx[j];
				int ny = curr.y + dy[j];
				if (ValidateCoordinate(nx, ny) && m_Table[nx][ny]->IsRoad() && !visited[nx][ny])
				{
					Point p = { nx, ny };
					q.push(p);
					visited[nx][ny] = true;
				}
			}
		}
	}

	return fieldsOnFire;
}