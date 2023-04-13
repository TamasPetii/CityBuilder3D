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
	while (m_id_set.find(i) != m_id_set.end()) i++; //keresnk egy 0-nl nagyobb id-t, ami mg nem foglalt
	m_id_set.emplace(i);
	m_networks.emplace_back(i);
	return i;
}

void RoadNetwork::AddToNetwork(GameField* field, int id) {
	for (auto& network : m_networks) {
		if (network.id != id) continue;
		if (field->IsZone()) network.zoneSet.emplace(field);
		if (field->IsRoad()) network.roadSet.emplace(field);
		if (field->IsBuilding()) network.buildingSet.emplace(field);
	}
}

void RoadNetwork::RemoveFromNetwork(GameField* field) {
	for (auto it = m_networks.begin(); it != m_networks.end(); ++it) {
		if (field->IsZone() && it->zoneSet.find(field) != it->zoneSet.end())
			it->zoneSet.erase(field);
		if (field->IsRoad() && it->roadSet.find(field) != it->roadSet.end())
			it->roadSet.erase(field);
		if (field->IsBuilding() && it->buildingSet.find(field) != it->buildingSet.end())
			it->buildingSet.erase(field);

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
	m_networks.erase(m_networks.begin() + vec_ind2);
	m_id_set.erase(id2);
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
		//Tbbi esetre nem ltom hogy mirt lenne szksg(pl t-zna), 
		//de knny hozzadni
		return true;
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

double RoadNetwork::GetSatisfaction(Zone* field) {
	bool stadiumBonus = false;
	bool policeBonus = false;
	int closestIndustrial = 10;
	double satisfaction = 0;

	for (auto& network : m_networks) {
		//Rendõrség, stadion vizsgálata
		if (network.zoneSet.find(field) == network.zoneSet.end()) continue;
		for (auto& b : network.buildingSet) {
			Building* building = dynamic_cast<Building*>(b);
			if (!stadiumBonus && building->IsStadium()) {
				if (distance(field, building) < 10) {
					satisfaction += 0.3;
					stadiumBonus = true;
				}
			}
			else if (!policeBonus && building->IsPoliceStation()) {
				if (distance(field, building) < 10) {
					satisfaction += 0.7;
					policeBonus = true;
				}
			}
		}

		//Közelben lévõ ipari zóna vizsgálata
		for (auto& z : network.zoneSet) {
			Zone* zone = dynamic_cast<Zone*>(z);
			if (zone->IsWorkingArea()) {
				WorkingArea* workingZone = dynamic_cast<WorkingArea*>(zone);
				if (workingZone->IsIndustrialArea()) {
					double d = distance(field, workingZone);
					if (d < closestIndustrial) closestIndustrial = (int)d;
				}
			}
		}
		
		if (closestIndustrial < 10) {
			satisfaction -= (10 - closestIndustrial) / 10; //0.9 - 0.1-et von le
		}
	}

	return satisfaction < 0 ? 0 : satisfaction;
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



