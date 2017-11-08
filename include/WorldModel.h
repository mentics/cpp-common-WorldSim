#pragma once
#include "MenticsCommon.h"
#include "Agent.h"

typedef uint64_t RealTime; // nanoseconds

class WorldModel;
PTRS(WorldModel)

struct Change {
	Change(RealTime at) : at(at) {}

	virtual void apply(WorldModelPtr model) = 0;

	RealTime at;
};
PTRS(Change)

class WorldModel {
public:
	AgentId createAgent() {
		agents.emplace_back(agents.size(), makeTrajZero(), makeTrajZero());
		return agents.back().id;
	}

	void forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler);

	Agent* agent(AgentId id) {
		return &agents[id];
	}

	void change(ChangeUniquePtr c);

	void reset(RealTime resetToTime);

private:
	std::vector<Agent> agents;
};