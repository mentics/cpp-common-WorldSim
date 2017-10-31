#pragma once
#include "MenticsCommon.h"
#include "Agent.h"

class Model {
public:
	AgentPtr createAgent() {
		agents.emplace_back(agents.size(),
			uniquePtr<BasicTrajectory>(0.0, 1.0E31, VZERO, VZERO, VZERO),
			uniquePtr<BasicTrajectory>(0.0, 1.0E31, VZERO, VZERO, VZERO));
		// TODO: this is a problem if we use std::vector because the pointer could point to something else later after erase/emplace's
		return NN_CHECK_ASSERT(&agents.back());
	}

	void forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler);

private:
	std::vector<Agent> agents;
};