#pragma once
#include "MenticsCommon.h"
#include "Agent.h"

class Model {
public:
	nn::nn<Agent*> createAgent() {
		agents.emplace_back(agents.size(),
			nn::nn_make_unique<BasicTrajectory>(0.0, 1.0E31, VZERO, VZERO, VZERO),
			nn::nn_make_unique<BasicTrajectory>(0.0, 1.0E31, VZERO, VZERO, VZERO));
		// TODO: this is a problem if we use std::vectory because the pointer could point to something else later after erase/emplace's
		return NN_CHECK_ASSERT(&agents.back());
	}

	void forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler);

private:
	std::vector<Agent> agents;
};