#include "RoadNetwork.h"

std::unordered_set<int> RoadNetwork::m_id_set;
std::vector<RoadNetwork::Network> RoadNetwork::m_networks;

int RoadNetwork::GetNetworkId(GameField* field) {
	for (auto& network : m_networks) {
		if (field->IsZone() && network.zoneSet.find(field) != network.zoneSet.end()) return network.id;
		if (field->IsRoad() && network.roadSet.find(field) != network.roadSet.end()) return network.id;
		if (field->IsBuilding() && network.buildingSet.find(field) != network.buildingSet.end()) return network.id;
	}
	return -1;
}

int RoadNetwork::CreateNetwork() {
	int i = 1;
	while (m_id_set.find(i) != m_id_set.end()) i++; //keresünk egy 0-nál nagyobb id-t, ami még nem foglalt
	m_id_set.emplace(i);
	m_networks.emplace_back(i);
	return i;
}

bool RoadNetwork::AddToNetwork(GameField* field, int id) {
	bool added = false;
	for (auto& network : m_networks) {
		if (network.id != id) continue;
		if (field->IsZone()) added = network.zoneSet.emplace(field).second;
		if (field->IsRoad()) added = network.roadSet.emplace(field).second;
		if (field->IsBuilding()) added = network.buildingSet.emplace(field).second;
	}
	return added;
}

void RoadNetwork::RemoveFromNetwork(GameField* field) {
	for (auto it = m_networks.begin(); it != m_networks.end(); ++it) {
		if (field->IsZone() && it->zoneSet.find(field) != it->zoneSet.end())
			it->zoneSet.erase(field);
		if (field->IsRoad() && it->roadSet.find(field) != it->roadSet.end())
			it->roadSet.erase(field);
		if (field->IsBuilding() && it->buildingSet.find(field) != it->buildingSet.end()) {
			it->buildingSet.erase(field);
			for (auto& zone : it->zoneSet) {
				RoadNetwork::SetZoneSatisfaction(zone);
			}
		}
			

		if (it->zoneSet.size() == 0 && it->roadSet.size() == 0 && it->buildingSet.size() == 0) {
			m_id_set.erase(it->id);
			it = m_networks.erase(it);
		}
	}
}

void RoadNetwork::MergeNetworks(int id1, int id2) { //id: a network id-je. vec_ind: a network indexe a vectorban
	if (id1 == id2) return;
	int vec_ind1 = -1;
	int vec_ind2 = -1;
	for (int i = 0; i < m_networks.size(); ++i) {
		if (id1 == m_networks[i].id) vec_ind1 = i;
		if (id2 == m_networks[i].id) vec_ind2 = i;
	}
	if (vec_ind1 == -1 || vec_ind2 == -1) return;
	RoadNetwork::m_networks[vec_ind1].zoneSet.insert( //2. network insertelse az 1.-be
		std::make_move_iterator(m_networks[vec_ind2].zoneSet.begin()), 
		std::make_move_iterator(m_networks[vec_ind2].zoneSet.end())
	);
	RoadNetwork::m_networks[vec_ind1].roadSet.insert(
		std::make_move_iterator(m_networks[vec_ind2].roadSet.begin()),
		std::make_move_iterator(m_networks[vec_ind2].roadSet.end())
	);
	RoadNetwork::m_networks[vec_ind1].buildingSet.insert(
		std::make_move_iterator(m_networks[vec_ind2].buildingSet.begin()),
		std::make_move_iterator(m_networks[vec_ind2].buildingSet.end())
	);
	int newNetworkId = m_networks[vec_ind1].id;
	m_networks.erase(m_networks.begin() + vec_ind2);
	m_id_set.erase(id2);
	for (auto& network : m_networks) {
		if (network.id != newNetworkId) continue;
		for (auto& zone : network.zoneSet) {
			RoadNetwork::SetZoneSatisfaction(zone);
		}
	} 
}

bool RoadNetwork::IsConnected(GameField* field1, GameField* field2) {
	for (auto& network : m_networks) {
		if (field1->IsZone() && field2->IsZone()) {
			if (network.zoneSet.find(field1) == network.zoneSet.end()) continue;
			if (network.zoneSet.find(field2) == network.zoneSet.end()) continue;
		}
		else if (field1->IsZone() && field2->IsBuilding()) {
			if (network.zoneSet.find(field1) == network.zoneSet.end()) continue;
			if (network.buildingSet.find(field2) == network.buildingSet.end()) continue;
		}
		else if (field1->IsBuilding() && field2->IsZone()) {
			if (network.buildingSet.find(field1) == network.buildingSet.end()) continue;
			if (network.zoneSet.find(field2) == network.zoneSet.end()) continue;
		}
		//Többi esetre nem látom hogy miért lenne szükség(pl út-zóna), 
		//de könnyû hozzáadni
		return true;
	}

	return false;
}

bool RoadNetwork::IsConnectedMultiple(GameField* field1, GameField* field2) {
	bool once = false;
	for (auto& network : m_networks) {
		if (field1->IsZone() && field2->IsZone()) {
			if (network.zoneSet.find(field1) == network.zoneSet.end()) continue;
			if (network.zoneSet.find(field2) == network.zoneSet.end()) continue;
		}
		else if (field1->IsZone() && field2->IsBuilding()) {
			if (network.zoneSet.find(field1) == network.zoneSet.end()) continue;
			if (network.buildingSet.find(field2) == network.buildingSet.end()) continue;
		}
		else if (field1->IsBuilding() && field2->IsZone()) {
			if (network.buildingSet.find(field1) == network.buildingSet.end()) continue;
			if (network.zoneSet.find(field2) == network.zoneSet.end()) continue;
		}
		if (!once) {
			once = true;
		} else {
			return true;
		}
	}
	return false;
}

Zone* RoadNetwork::FindEmptyWorkingArea(Zone* field, float ratio) {
	if (field == nullptr) return nullptr;
	float minDistanceI = 100000;
	Zone* closestZoneI = nullptr;
	float minDistanceS = 100000;
	Zone* closestZoneS = nullptr;

	for (auto& network : m_networks) {
		if (network.zoneSet.find(field) == network.zoneSet.end()) continue;

		for (auto& otherField : network.zoneSet) {
			if (WorkingArea* workingArea = dynamic_cast<WorkingArea*>(otherField)) {
				if (workingArea->IsThereEmptySpace()) {
					float d = (float)distance(workingArea, field);
					if (workingArea->IsIndustrialArea()) {
						if (d < minDistanceI) {
							minDistanceI = d;
							closestZoneI = workingArea;
						}
					}
					else {
						if (d < minDistanceS) {
							minDistanceS = d;
							closestZoneS = workingArea;
						}
					}
				}
			}

		}
	}
	if (ratio > 1.5) { //több service van ezért industrial kell
		if (closestZoneI == nullptr) return closestZoneS;
		else return closestZoneI;
	}
	else if (ratio < 0.66) {
		if (closestZoneS == nullptr) return closestZoneI;
		else return closestZoneS;
	}
	else {
		if (minDistanceI < minDistanceS && closestZoneI != nullptr) return closestZoneI;
		if (minDistanceS <= minDistanceI && closestZoneS != nullptr) return closestZoneS;
		if (closestZoneI == nullptr) return closestZoneS;
		if (closestZoneS == nullptr) return closestZoneI;
	}

	//Should not reach this point
	return nullptr;
}

std::string RoadNetwork::NetworksToString() {
	std::string s = "";
	int i = 1;
	for (auto& network : m_networks) {
		s += std::to_string(i) + ". network: " + std::to_string(
			network.zoneSet.size() + network.roadSet.size() + network.buildingSet.size()) + "\n";
		i++;
	}
	return s;
}

void RoadNetwork::ResetNetworks() {
	m_id_set.clear();
	for (auto& network : m_networks) {
		network.zoneSet.clear();
		network.roadSet.clear();
		network.buildingSet.clear();
	}
	m_networks.clear();
}

Zone* RoadNetwork::FindEmptyResidentialArea() {
	for (auto& network : m_networks) {
		for (auto& z : network.zoneSet) {
			Zone* zone = dynamic_cast<Zone*>(z);
			if (zone->IsResidentalArea() && zone->IsThereEmptySpace())
				return zone;
		}
	}
	return nullptr;
}

double RoadNetwork::distance(GameField* g1, GameField* g2) {
	return sqrt(pow(g1->Get_X() - g2->Get_X(), 2) + pow(g1->Get_Y() - g2->Get_Y(), 2));
}

void RoadNetwork::AddToNetworkSatisfaction(GameField* field, int id) {
	for (auto& network : m_networks) {
		if (network.id != id) continue;
		for (auto& z : network.zoneSet) {
			if (Building* building = dynamic_cast<Building*>(field)) {
				Zone* zone = dynamic_cast<Zone*>(z);
				int d = (int)distance(building, zone);
				if (d < 10 && !IsConnectedMultiple(zone, building)) {//csak akkor adjuk hozzá, ha nincsenek többször összekötve
					if (building->IsPoliceStation()) {
						zone->Add_Safety((10 - d) / 10.0f);
					}
					else {
						zone->Add_Satisfaction((10 - d) / 10.0f * building->GetBuildingSatisfaction());
					}

					if (building->IsFireStation())
					{
						zone->Add_FireRate((10 - d) / 10.0f);
					}
				}
			}
		}
		/*
		//Tűz esélye a kiszolgáló épületeket is befolyásolja nem csak a zónákat
		for (auto& b : network.buildingSet)
		{
			if (Building* building = dynamic_cast<Building*>(field))
			{
				Building* current_building = dynamic_cast<Building*>(b);
				int d = distance(building, current_building);
				if (d < 10 && !IsConnectedMultiple(current_building, building))
				{
					if (building->IsFireStation())
					{
						current_building->Add_FireRate((10 - d) / 10.0);
					}
				}
			}
		}
		*/
	}
}

void RoadNetwork::SetZoneSatisfaction(GameField* field) {
	Zone* zone = dynamic_cast<Zone*>(field);
	if (zone == nullptr) return;
	float satisfaction = 0;
	float safety = 0;
	float firerate = 0;
	std::unordered_set<Building*> visitedBuilding;

	for (auto& network : m_networks) {
		if (network.zoneSet.find(zone) == network.zoneSet.end()) continue;
		for (auto& b : network.buildingSet) {
			Building* building = dynamic_cast<Building*>(b);
			int d = (int)distance(building, zone);
			if (d < 10 && visitedBuilding.find(building) == visitedBuilding.end()) {
				if (building->IsPoliceStation()) {
					safety += (10 - d) / 10.0f;
					visitedBuilding.emplace(building);
				}
				else {
					satisfaction += (10 - d) / 10.0f * building->GetBuildingSatisfaction();
					visitedBuilding.emplace(building);
				}

				if (building->IsFireStation())
				{
					firerate += (10 - d) / 10.0f;
				}
			}
		}
	}

	zone->Set_Satisfaction(satisfaction);
	zone->Set_Safety(safety);
	zone->Set_FireRate(firerate);
}

Zone* RoadNetwork::FindOptimalResidentialArea(float happiness) {
	float moveInThreshold = happiness * 3;
	float industrialPenalty = 0;
	for (auto& network : m_networks) {
		for (auto& z : network.zoneSet) {
			Zone* zone = dynamic_cast<Zone*>(z);
			if (!(zone->IsResidentalArea() && zone->IsThereEmptySpace()))
				continue;

			//industrialPenalty: közvetlenül melletted lévõ ipari zóna -0.9, 9 blokkra lévõ -0.1;
			industrialPenalty = zone->Get_IndustrialPenalty();

			for (auto& w : network.zoneSet) {
				Zone* wZone = dynamic_cast<Zone*>(w);
				if (!(wZone->IsWorkingArea() && wZone->IsThereEmptySpace()))
					continue;
				float d = (float)distance(wZone, zone);
				float workDistancePenalty = -(d / 20 - 0.05f); //ha mellette van 0 penalty, különben 0.05esével nõ
				if (industrialPenalty < -0.5) industrialPenalty = -0.5;
				//szóval ha happiness 30%, akkor a threshold 0.9 lesz,
				//ami megengedi a beköltözést, ha: van 5 blokkon belül ipari de van üres munkahely 8 blokkon belül,
				//vagy nincs a közelben ipari és van üres munkahely 18 blokkon belül(vagy valami köztes)
				if (moveInThreshold + industrialPenalty + workDistancePenalty > 0) {
					return zone;
				}
			}
		}
	}
	
	return nullptr;
}

void RoadNetwork::ApplyToAllZones(const ZoneFunction& func)
{
	for (auto& network : m_networks)
	{
		for (auto& zone : network.zoneSet)
		{
			func(zone);
		}
	}
}

void RoadNetwork::ApplyToAllBuilding(const ZoneFunction& func)
{
	for (auto& network : m_networks)
	{
		for (auto& building : network.buildingSet)
		{
			func(building);
		}
	}
}
