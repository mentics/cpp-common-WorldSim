#include "stdafx.h"
#include "WorldModel.h"

void WorldModel::forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler) {
	if (agents.size() > max) {
		throw "Insufficient buffer size";
	}
	for (auto& agent : agents) {
		handler(agent);
	}
}
