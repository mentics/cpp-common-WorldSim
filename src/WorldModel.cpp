#include "stdafx.h"
#include "WorldModel.h"


AgentId WorldModel::createAgent() {
	agents.emplace_back(agents.size(), makeTrajZero(), makeTrajZero());
	return agents.back().id;
}

Agent* WorldModel::agent(AgentId id) {
	return id < agents.size() ? &agents[id] : nullptr;
}

void WorldModel::forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler) {
	if (agents.size() > max) {
		throw "Insufficient buffer size";
	}
	for (auto& agent : agents) {
		handler(agent);
	}
}

void WorldModel::change(ChangeUniquePtr c) {
	// TODO: assert the correct thread?
	// TODO: store change
	c->apply(nn::nn_addr(*this));
}

void WorldModel::reset(RealTime resetToTime) {
	// TODO: impl
}
