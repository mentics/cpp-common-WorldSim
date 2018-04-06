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
		Agent(Agent<TimeType>&&) = default;
		
		Agent(const AgentId id, TrajectoryUniquePtr&& trajectory, TeamId team = 2)
			: id(id), team(team), trajectory(std::move(trajectory)), thoughtPeriod(0), reactionTime(0), perceptionDelay(0)
		{
		}

		AgentId id;
		SignalValue<uint64_t,TimeType> thoughtPeriod; 
		SignalUnique<Trajectory, TimeType> trajectory;
		
		// Represents which team the agent is on. Used to identify friendlies and enemies. 
		// Default value is 2 for enemy team.Value is 1 for single player's team.
		SignalValue<TeamId, TimeType> team;
		SignalValue<TimeType> reactionTime;
		SignalValue<TimeType> perceptionDelay;
		
		void reset(TimeType resetTime)
		{
			thoughtPeriod.reset(resetTime);
			trajectory.reset(resetTime);
			team.reset(resetTime);
			reactionTime.reset(resetTime);
			perceptionDelay.reset(resetTime);
		}
		
	};
	PTRS1(Agent, TimeType)


	class FullAgent : public Agent<>
	{
	public:
		FullAgent(const AgentId id, TrajectoryUniquePtr&& trajectory)
			: Agent(id, std::move(trajectory)) 
		{
		}
	};

	class Boss : public FullAgent {
	public:
		Boss(const AgentId id, TrajectoryUniquePtr&& trajectory)
			: FullAgent(id, std::move(trajectory)) 
		{} 

	};
	class Shot : public FullAgent {};
	class Minion : public FullAgent {};
	

	



	
}