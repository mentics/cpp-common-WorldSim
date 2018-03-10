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
		//Agent() {}
		Agent(const AgentId id, Signal<TrajectoryUniquePtr, TimeType>, TeamId team = 2)
			: id(id), team(team) trajectory(trajectory)
		{
		}


		AgentId id;
		Signal<TimeType,TimeType> thoughtPeriod; // not sure? <TimeType, TimeType>
		Signal<nn::nn_unique_ptr<Trajectory>, TimeType> trajectory;
	
		// Represents which team the agent is on. Used to identify friendlies and enemies. 
		// Default value is 2 for enemy team.Value is 1 for single player's team.
		Signal<TeamId, TimeType> team;
		Signal<TimeType> reactionTime;
		Signal<TimeType> perceptionDelay;

		void reset(TimeType resetTime)
		{
			thoughtPeriod.reset(resetTime);
			trajectory.reset(resetTime);
			team.reset(resetTime);
			reactionTime.reset(resetTime);
			perceptionDelay.reset(resetTime);
		}
		//virtual ~Agent() = 0;
	};
	PTRS1(Agent, TimeType)

	class Boss : public Agent<> {};
	class Shot : public Agent<> {};
	class Minion : public Agent<> {};
	

	

	//PTRS(Agent<typename TimeType>)     

		// just so Agent is abstract, replace once any function gets added 
		//Agent::~Agent() {} //  Causes errors because other parts of the code do instantiate it, we should find them and change them


	
}