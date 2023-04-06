#pragma once

#include <vector>
#include <utility>
#include <unordered_set>

class RoadNetwork
{
public:
	static int GetNetworkId(int, int);
	static void CreateNetwork();
	static void AddToNetwork(int, int, int);
	static void RemoveFromNetwork(int, int, int);
	static void MergeNetworks(int, int);
	static bool IsConnected(int, int, int, int);

private:
	class Network {
	public:
		Network(int i) : id(i) {}
		const int id;
		std::unordered_set<std::pair<int, int>> fieldSet;
	};

	static std::unordered_set<int> m_id_set; //minden networknek egy különbözõ id-ja lesz

	static std::vector<Network> m_networks;
};

