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

void RoadNetwork::CreateNetwork() {
	int i = 1;
	while (m_id_set.find(i) != end(m_id_set)) i++; //keresünk egy 0-nál nagyobb id-t, ami még nem foglalt
	m_id_set.emplace(i);
	m_networks.emplace_back(i);
}


/*
void RoadNetwork::AddToNetwork(GameField* field, int id) {
	for (auto& network : m_networks) {
		if (network.id != id) continue;

		network.fieldSet.emplace(field);
	}
}

void RoadNetwork::RemoveFromNetwork(GameField* field, int id) {
	int i = 0;
	for (auto& network : m_networks) {
		i++;
		if (network.id != id) continue;

		network.fieldSet.erase(field);
		if (network.fieldSet.size() == 0) {
			m_networks.erase(m_networks.begin() + i);
			m_id_set.erase(network.id);
		}
	}
}

void RoadNetwork::MergeNetworks(int id1, int id2) { //id: a network id-je. vec_ind: a network indexe a vectorban
	int vec_ind1 = -1;
	int vec_ind2 = -1;
	for (int i = 0; i < m_networks.size(); ++i) {
		if (id1 == m_networks[i].id) vec_ind1 = i;
		if (id2 == m_networks[i].id) vec_ind2 = i;
	}
	if (vec_ind1 == -1 || vec_ind2 == -1) return;
	RoadNetwork::m_networks[vec_ind1].fieldSet.insert( //2. network insertelése az 1.-be
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

GameField* RoadNetwork::FindEmptyWorkingArea(GameField*) {
	for (auto& network : m_networks) {
			
	}
	return nullptr;
}

*/
