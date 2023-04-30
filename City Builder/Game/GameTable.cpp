#include "GameTable.h"
#include "RoadNetwork.h"

bool GameTable::changed = false;

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

void GameTable::Set_TableValue(int x, int y, GameField* field)
{
	delete m_Table[x][y];
	m_Table[x][y] = field;
	SetBuildingNetwork(x, y);
}

void GameTable::Set_TableValue(int x, int y, FieldType type) {
	if (!m_Table[x][y]->IsEmpty()) { //törlés
		if (!(type == EMPTY || type == CRATER)) return;
		DeleteField(x, y, type);
		return;
	}
	else {
		m_Table[x][y] = GameField::CreateField(type, x, y);
		GameField* newField = m_Table[x][y];
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
		//TODO: megnézni, hogy van -e a környezetben közvetlen rálátású erdõ,
		//illetve hogy blokkoltuk -e valakinek a rálátását.
	}
	else if (type == FOREST) {
		//TODO: növelni a szomszédos mezõk elégedettségét, ha rálátnak az erdõre
	}
}

void GameTable::DeleteField(int x, int y, FieldType type) {
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
						m_Table[new_x][new_y] = GameField::CreateField(type, new_x, new_y);
					}
				}
			}
		}

		RoadNetwork::RemoveFromNetwork(m_Table[x][y]);
	}
	delete(m_Table[x][y]);

	m_Table[x][y] = GameField::CreateField(type, x, y);
	GameField* newField = m_Table[x][y];

	if (isRoad) RebuildRoadNetwork();
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
	//Magyarázat: a []-ben adjuk meg, hogy mit szeretnénk a lambdában használni(capture list)
	//az adj pedig az éppen sorrakerülõ szomszéd
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

void GameTable::SetBuildingNetwork(int x, int y) {
	GameField* newBuilding = m_Table[x][y];
	LoopThroughNeighbors(x, y, [this, newBuilding](GameField* adj) {
		if (Road* road = dynamic_cast<Road*>(adj)) {
			int id = RoadNetwork::GetNetworkId(adj);
			bool added = RoadNetwork::AddToNetwork(newBuilding, id);
			//ha added, tehát még nem volt benne a networkben, akkor számoljuk az elégedettséget is
			if (added) RoadNetwork::AddToNetworkSatisfaction(newBuilding, id);
		}
	});
}

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

float GameTable::distance(GameField* g1, GameField* g2) {
	return sqrt(pow(g1->Get_X() - g2->Get_X(), 2) + pow(g1->Get_Y() - g2->Get_Y(), 2));
}

void GameTable::AddIndustrialAreaBonus(GameField* f, int placed) {
	for (int i = -9; i <= 9; i++) {
		for (int j = -9; j <= 9; j++) {
			if (f->Get_X() + i < 0 || f->Get_X() + i >= m_TableSize || f->Get_Y() + j < 0 || f->Get_Y() + j >= m_TableSize) continue;
			if (Zone* zone = dynamic_cast<Zone*>(m_Table[f->Get_X() + i][f->Get_Y() + j])) {
				if (zone->IsResidentalArea()) {
					int d = distance(f, zone);
					float penalty = (10 - d) / 10.0;
					//placed 1, ha lerak, -1, ha töröl
					zone->Add_IndustrialPenalty(placed * -1 * penalty);
				}
			}

		}
	}
}

void GameTable::CheckZoneIndustrialBonus(GameField* f) {
	Zone* residentialZone = dynamic_cast<Zone*>(f);
	for (int i = -9; i <= 9; i++) {
		for (int j = -9; j <= 9; j++) {
			if (f->Get_X() + i < 0 || f->Get_X() + i >= m_TableSize || f->Get_Y() + j < 0 || f->Get_Y() + j >= m_TableSize) continue;
			if (Zone* zone = dynamic_cast<Zone*>(m_Table[f->Get_X() + i][f->Get_Y() + j])) {
				if (WorkingArea* w = dynamic_cast<WorkingArea*>(zone)) {
					if (w->IsIndustrialArea()) {
						int d = distance(w, f);
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

bool GameTable::ValidateCoordinate(int c)
{
	return c >= 0 && c < m_Table.size();
}

bool GameTable::ValidateCoordinate(int c1, int c2)
{
	return ValidateCoordinate(c1) && ValidateCoordinate(c2);
}

bool GameTable::IsBuildableField(int x, int y)
{
	return ValidateCoordinate(x, y) && m_Table[x][y]->IsEmpty();
}


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

void GameTable::SimulateFire(GameField* field)
{
	//Fire appears randomly
	if ((field->IsZone() || field->IsBuilding()) && field->Get_Type() != FIRESTATION)
	{
		field->RandomFire();
		changed = changed || field->OnFire();
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
					bool type = (m_Table[nbX][nbY]->IsZone() || m_Table[nbX][nbY]->IsBuilding()) && m_Table[nbX][nbY]->Get_Type() != FIRESTATION;

					if (type && ValidateCoordinate(nbX, nbY) && !m_Table[nbX][nbY]->OnFire())
					{
						bool fire = (rand() % 3 == 0);
						m_Table[nbX][nbY]->OnFire() = fire;

						changed = changed || fire;
					}
				}
			}
		}
	}

	if (field->FireCounter == 0)
	{
		this->Set_TableValue(field->Get_X(), field->Get_Y(), EMPTY);
		changed = true;
	}
}

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