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
	Agent(const AgentId id, nn::nn<std::unique_ptr<Trajectory>> trajectory, nn::nn<std::unique_ptr<Trajectory>> visibleTrajectory)
		: id(id), trajectory(std::move(trajectory)), visibleTrajectory(std::move(visibleTrajectory)) {}

	const AgentId id;
	nn::nn<std::unique_ptr<Trajectory>> trajectory;
	nn::nn<std::unique_ptr<Trajectory>> visibleTrajectory;
};