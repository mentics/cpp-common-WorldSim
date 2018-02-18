#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {
	void WorldModel::forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler) {
		if (agents.size() > max) {
			throw "Insufficient buffer size";
		}
		for (auto& agent : agents) {
			handler(agent);
		}
	}

	void WorldModel::change(Change2UniquePtr c) {
		// TODO: assert the correct thread?
		// TODO: store change
		c->apply(nn::nn_addr(*this));
	}

	void WorldModel::reset(RealTime resetToTime) {
		reset.reset(resetToTime);
	}
}