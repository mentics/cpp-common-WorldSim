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
	Agent(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, uint16_t team = 2)
		: id(id), trajectory(trajectory), visibleTrajectory(visibleTrajectory), team(team) {}

	const AgentId id;
	nn::nn_shared_ptr<Trajectory> trajectory;
	nn::nn_shared_ptr<Trajectory> visibleTrajectory;
	// Represents which team the agent is on. Used to identify friendlies and enemies. 
	// Default value is 2 for enemy team.Value is 1 for single player's team.
	uint16_t team;
	virtual ~Agent() = 0;
};
PTRS(Agent)

// just so Agent is abstract, replace once any function gets added 
Agent::~Agent() {}