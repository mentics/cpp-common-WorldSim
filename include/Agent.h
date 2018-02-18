#pragma once

#include "MenticsCommon.h"
#include "MenticsCommonTest.h"
#include "MenticsMath.h"
#include "Trajectory.h"
#include "Quip.h"
#include <vector>


namespace MenticsGame {
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
		//virtual ~Agent() = 0;
	};
	PTRS(Agent)

		// just so Agent is abstract, replace once any function gets added 
		//Agent::~Agent() {} //  Causes errors because other parts of the code do instantiate it, we should find them and change them

	class Boss : public Quip {};
	class Minion : public Quip {};
	class Shot : public Quip {};

	struct AllAgents
	{
		std::vector<Boss> bosses; 
		std::vector<Minion> minions;  
		std::vector<Shot> shots;

		template <typename T>
		void forEach(T f) 
		{
			for (Boss boss : bosses) f(boss);
			for (Minion minion : minions) f(minion);
			for (Shot shot : shots) f(shot);
		}

	};
}