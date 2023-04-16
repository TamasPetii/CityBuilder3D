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

void GameTable::Set_TableValue(int x, int y, FieldType type) {
	if (!m_Table[x][y]->IsEmpty()) { //törlés
		if (type != EMPTY) return;
		DeleteField(x, y);
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

void GameTable::DeleteField(int x, int y) {
	bool isRoad = dynamic_cast<Road*>(m_Table[x][y]);
	bool isIndustrial = false;
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

		RoadNetwork::RemoveFromNetwork(m_Table[x][y]);
	}
	delete(m_Table[x][y]);

	m_Table[x][y] = GameField::CreateField(EMPTY, x, y);
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
