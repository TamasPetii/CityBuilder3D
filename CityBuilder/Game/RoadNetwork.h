#pragma once

#include <vector>
#include <unordered_set>
#include "GameFields/GameField.h"
#include "GameFields/Zones/_ZoneHeaders.h"
#include "GameFields/Buildings/_BuildingHeaders.h"
#include <string>
#include <cmath>
#include <functional>

class RoadNetwork
{
public:
	static int GetNetworkId(GameField*);
	static int CreateNetwork();
	static bool AddToNetwork(GameField*, int);
	static void RemoveFromNetwork(GameField*);
	static void MergeNetworks(int, int);
	static bool IsConnected(GameField*, GameField*);
	static Zone* FindEmptyWorkingArea(Zone*, float);
	static void ResetNetworks();
	static Zone* FindEmptyResidentialArea();
	static std::string NetworksToString();
	static void AddToNetworkSatisfaction(GameField*, int);
	static void SetZoneSatisfaction(GameField*);
	static bool IsConnectedMultiple(GameField*, GameField*);
	static Zone* FindOptimalResidentialArea(float);

	using ZoneFunction = std::function<void(GameField* const)>;
	
	static void ApplyToAllZones(const ZoneFunction& func);
	static void ApplyToAllBuilding(const ZoneFunction& func);

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

	static double distance(GameField*, GameField*);
};

