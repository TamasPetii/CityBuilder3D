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
	while (m_id_set.find(i) != m_id_set.end()) i++; //keres�nk egy 0-n�l nagyobb id-t, ami m�g nem foglalt
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
		//T�bbi esetre nem l�tom hogy mi�rt lenne sz�ks�g(pl �t-z�na), 
		//de k�nny� hozz�adni
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

Zone* RoadNetwork::FindEmptyWorkingArea(Zone* field) {
	if (field == nullptr) return nullptr;

for (auto& network : m_networks) {
	if (network.zoneSet.find(field) == network.zoneSet.end()) continue;

	for (auto& otherField : network.zoneSet) {
		if (WorkingArea* workingArea = dynamic_cast<WorkingArea*>(otherField)) {
			if (workingArea->Get_ZoneDetails().contain < workingArea->Get_ZoneDetails().capacity)
				return workingArea;
		}

	}
}
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
			if (zone->IsResidentalArea() && zone->Get_ZoneDetails().contain < zone->Get_ZoneDetails().capacity)
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
				int d = distance(building, zone);
				if (d < 10 && !IsConnectedMultiple(zone, building)) {//csak akkor adjuk hozz�, ha nincsenek t�bbsz�r �sszek�tve
					if (building->IsPoliceStation()) {
						zone->Add_Safety((10 - d) / 10.0);
					}
					else {
						zone->Add_Satisfaction((10 - d) / 10.0 * building->GetBuildingSatisfaction());
					}
				}
			}
		}
	}
}

void RoadNetwork::SetZoneSatisfaction(GameField* field) {
	Zone* zone = dynamic_cast<Zone*>(field);
	if (zone == nullptr) return;
	float satisfaction = 0;
	float safety = 0;
	std::unordered_set<Building*> visitedBuilding;

	for (auto& network : m_networks) {
		if (network.zoneSet.find(zone) == network.zoneSet.end()) continue;
		for (auto& b : network.buildingSet) {
			Building* building = dynamic_cast<Building*>(b);
			int d = distance(building, zone);
			if (d < 10 && visitedBuilding.find(building) == visitedBuilding.end()) {
				if (building->IsPoliceStation()) {
					safety += (10 - d) / 10.0;
					visitedBuilding.emplace(building);
				}
				else {
					satisfaction += (10 - d) / 10.0 * building->GetBuildingSatisfaction();
					visitedBuilding.emplace(building);
				}
			}
		}
	}

	zone->Set_Satisfaction(satisfaction);
	zone->Set_Safety(safety);
}



