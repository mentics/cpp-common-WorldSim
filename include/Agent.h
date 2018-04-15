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
	
template<typename TimeType>
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
	SignalValue<TimeType, TimeType> reactionTime;
	SignalValue<TimeType, TimeType> perceptionDelay;
		
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
#define AgentP AgentPtr<TimeType>
#define AgentUP AgentUniquePtr<TimeType>

template<typename TimeType>
class FullAgent : public Agent<TimeType>
{
public:
	FullAgent(const AgentId id, TrajectoryUniquePtr&& trajectory)
		: Agent(id, std::move(trajectory)) 
	{
	}
};

template<typename TimeType>
class Boss : public FullAgent<TimeType> {
public:
	Boss(const AgentId id, TrajectoryUniquePtr&& trajectory)
		: FullAgent(id, std::move(trajectory)) 
	{} 
};
PTRS1(Boss, TimeType)
#define BossP BossPtr<TimeType>
#define BossUP BossUniquePtr<TimeType>

template<typename TimeType>
class Minion : public FullAgent<TimeType> {};
PTRS1(Minion, TimeType)
#define MinionP MinionPtr<TimeType>
#define MinionUP MinionUniquePtr<TimeType>

template<typename TimeType>
class Shot : public Agent<TimeType> {};
PTRS1(Shot, TimeType)
#define ShotP ShotPtr<TimeType>
#define ShotUP ShotUniquePtr<TimeType>

}