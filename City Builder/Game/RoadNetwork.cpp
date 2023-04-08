#include "RoadNetwork.h"

std::unordered_set<int> RoadNetwork::m_id_set;
std::vector<RoadNetwork::Network> RoadNetwork::m_networks;

int RoadNetwork::GetNetworkId(GameField* field) {
	for (auto& network : m_networks) {
		if (network.fieldSet.find(field) != network.fieldSet.end())
			return network.id;
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

void RoadNetwork::AddToNetwork(GameField* field, int id) {
	for (auto& network : m_networks) {
		if (network.id != id) continue;

		network.fieldSet.emplace(field);
	}
}

void RoadNetwork::RemoveFromNetwork(GameField* field) {
	for (auto it = m_networks.begin(); it != m_networks.end(); ++it) {
		if (it->fieldSet.find(field) == it->fieldSet.end()) continue;

		it->fieldSet.erase(field);
		if (it->fieldSet.size() == 0) {
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
	RoadNetwork::m_networks[vec_ind1].fieldSet.insert( //2. network insertel�se az 1.-be
		std::make_move_iterator(m_networks[vec_ind2].fieldSet.begin()), 
		std::make_move_iterator(m_networks[vec_ind2].fieldSet.end())
	);
	m_networks.erase(m_networks.begin() + vec_ind2);
	m_id_set.erase(id2);
}

bool RoadNetwork::IsConnected(GameField* field1, GameField* field2) {
	for (auto& network : m_networks) {
		if (network.fieldSet.find(field1) == network.fieldSet.end()) continue;
		if (network.fieldSet.find(field2) == network.fieldSet.end()) continue;
		return true;
	}

	return false;
}

GameField* RoadNetwork::FindEmptyWorkingArea(GameField* field) {
	for (auto& network : m_networks) {
		if (network.fieldSet.find(field) == network.fieldSet.end()) continue;

		for (auto& otherField : network.fieldSet) {
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
		s += std::to_string(i) + ". network: " + std::to_string(network.fieldSet.size()) + "\n";
		i++;
	}
	return s;
}

void RoadNetwork::ResetNetworks() {
	m_id_set.clear();
	for (auto& network : m_networks) {
		network.fieldSet.clear();
	}
	m_networks.clear();
}


