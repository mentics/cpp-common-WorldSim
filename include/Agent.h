#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Trajectory.h"

typedef uint64_t AgentId;
typedef uint32_t AgentIndex;

struct AgentPosVelAcc {
	AgentPosVelAcc() {}
	AgentPosVelAcc(AgentId agentId, PosVelAcc pva) : agentId(agentId), pva(pva) {}
	AgentId agentId;
	PosVelAcc pva;
};

struct Agent {
	Agent(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory)
		: id(id), trajectory(trajectory), visibleTrajectory(visibleTrajectory) {}

	const AgentId id;
	nn::nn_shared_ptr<Trajectory> trajectory;
	nn::nn_shared_ptr<Trajectory> visibleTrajectory;
};
PTRS(Agent)
