#pragma once

#include <vector>
#include <unordered_set>
#include "GameFields/GameField.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include "GameFields/Buildings/_BuildingHeaders.h"
#include <string>

class RoadNetwork
{
public:
	static int GetNetworkId(GameField*);
	static int CreateNetwork();
	static void AddToNetwork(GameField*, int);
	static void RemoveFromNetwork(GameField*);
	static void MergeNetworks(int, int);
	static bool IsConnected(GameField*, GameField*);
	static GameField* FindEmptyWorkingArea(Zone*);
	static void ResetNetworks();
	int GetSatisfaction(Zone* field);

	static std::string NetworksToString();

private:
	class Network {
	public:
		Network(int i) : id(i) {}
		int id;
		std::unordered_set<GameField*> zoneSet;
			std::unordered_set<GameField*> roadSet;
		std::unordered_set<GameField*> buildingSet;
	};

	static std::unordered_set<int> m_id_set; //minden networknek egy különbözõ id-ja lesz

	static std::vector<Network> m_networks;
};

