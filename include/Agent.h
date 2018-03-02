#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Trajectory.h"
#include "Signal.h"
#include <vector>


namespace MenticsGame {

	typedef uint16_t TeamId;
	typedef uint64_t AgentId;
	typedef uint32_t AgentIndex;

	struct AgentPosVelAcc {
		AgentPosVelAcc() {}
		AgentPosVelAcc(AgentId agentId, PosVelAcc pva) : agentId(agentId), pva(pva) {}
		AgentId agentId;
		PosVelAcc pva;
	};

	template<typename TimeType = TimePoint>
	struct Agent {
		Agent() {}
		Agent(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, TeamId team = 2)
			: id(id), trajectory(trajectory), visibleTrajectory(visibleTrajectory), team(team) {}

		const AgentId id;
		Signal<TimeType,TimeType> thoughtPeriod; // not sure?
		Signal<Trajectory*, TimeType> trajectory;
	
		// Represents which team the agent is on. Used to identify friendlies and enemies. 
		// Default value is 2 for enemy team.Value is 1 for single player's team.
		Signal<TeamId, TimeType> team;
		Signal<TimeType> reactionTime; 
		Signal<TimeType> perceptionDelay;
		bool deleted = false;
		//virtual ~Agent() = 0;
	};
	PTRS1(Agent, TimeType)

	class Boss : public Agent<> {};
	class Minion : public Agent<> {};
	class Shot : public Agent<> {};

	

	//PTRS(Agent<typename TimeType>)     

		// just so Agent is abstract, replace once any function gets added 
		//Agent::~Agent() {} //  Causes errors because other parts of the code do instantiate it, we should find them and change them


	
}