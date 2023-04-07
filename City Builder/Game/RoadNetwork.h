#pragma once

#include <vector>
#include <unordered_set>
#include "GameFields/GameField.h"

class RoadNetwork
{
public:
	static int GetNetworkId(GameField*);
	static void CreateNetwork();
	static void AddToNetwork(GameField*, int);
	static void RemoveFromNetwork(GameField*, int);
	static void MergeNetworks(int, int);
	static bool IsConnected(GameField*, GameField*);
	static GameField* FindEmptyWorkingArea(GameField*);

private:
	class Network {
	public:
		Network(int i) : id(i) {}
		const int id;
		std::unordered_set<GameField*> fieldSet;

		//Network(const Network&) = delete;
		//Network& operator=(const Network&) = delete;

		Network(const Network& other) : id(other.id), fieldSet(other.fieldSet) {}

		Network(Network&& other) : id(std::move(other.id)), fieldSet(std::move(other.fieldSet)) {}
	};

	static std::unordered_set<int> m_id_set; //minden networknek egy különbözõ id-ja lesz

	static std::vector<Network> m_networks;
};

