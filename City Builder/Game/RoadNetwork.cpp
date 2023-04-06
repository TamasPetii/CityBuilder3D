#include "RoadNetwork.h"

std::unordered_set<int> RoadNetwork::m_id_set;
std::vector<RoadNetwork::Network> RoadNetwork::m_networks;

int RoadNetwork::GetNetworkId(int x, int y) {
	std::pair<int, int> coords = { x, y };

	for (auto& network : m_networks) {
		if (network.fieldSet.find(coords) != network.fieldSet.end())
			return network.id;
	}
	return -1;
}

void RoadNetwork::CreateNetwork() {
	int i = 1;
	while (m_id_set.find(i) != end(m_id_set)) i++; //keresünk egy 0-nál nagyobb id-t, ami még nem foglalt
	m_id_set.emplace(i);
	Network network(i);
	m_networks.push_back(network);
}

void RoadNetwork::AddToNetwork(int x, int y, int id) {
	std::pair<int, int> coords = { x, y };
	for (auto& network : m_networks) {
		if (network.id != id) continue;

		network.fieldSet.emplace(coords);
	}
}

void RoadNetwork::RemoveFromNetwork(int x, int y, int id) {
	std::pair<int, int> coords = { x, y };
	int i = 0;
	for (auto& network : m_networks) {
		i++;
		if (network.id != id) continue;

		network.fieldSet.erase(coords);
		if (network.fieldSet.size() == 0) {
			m_networks.erase(m_networks.begin() + i);
			m_id_set.erase(network.id);
		}
	}
}

void RoadNetwork::MergeNetworks(int id1, int id2) {
	int network1;
	int network2;
	for (int i = 0; i < m_networks.size(); ++i) {
		if (id1 == m_networks[i].id) network1 = id1;
		if (id2 == m_networks[i].id) network2 = id2;
	}
	RoadNetwork::m_networks[network1].fieldSet.insert( //2. network insertelése az 1.-be
		std::make_move_iterator(m_networks[network2].fieldSet.begin()), 
		std::make_move_iterator(m_networks[network2].fieldSet.end())
	);
	m_networks.erase(m_networks.begin() + network2);
	m_id_set.erase(network2);
}

bool RoadNetwork::IsConnected(int x1, int y1, int x2, int y2) {
	std::pair<int, int> coord1 = { x1, y1 };
	std::pair<int, int> coord2 = { x2, y2 };

	for (auto& network : m_networks) {
		if (network.fieldSet.find(coord1) == network.fieldSet.end()) continue;
		if (network.fieldSet.find(coord2) == network.fieldSet.end()) continue;
		return true;
	}

	return false;
}
