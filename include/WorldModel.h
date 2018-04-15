#pragma once

#include "Agent.h"
#include "Quip.h"
#include "Signal.h"

namespace MenticsGame {

template<typename TimeType>
struct AllAgents {
	ONLY_MOVE(AllAgents);
public:
	SignalCollection<Boss<TimeType>, TimeType> bosses;
	SignalCollection<Minion<TimeType>, TimeType> minions;
	SignalCollection<Shot<TimeType>, TimeType> shots;
	SignalCollection<Quip<TimeType>, TimeType> quips;

	AllAgents() {}

	void forEach(std::function<void(AgentPtr<TimeType>)> f, TimeType now) {
		bosses.forEach(now, f);
		minions.forEach(now, f);
		shots.forEach(now, f);
		quips.forEach(now, f);
	}
		
	void reset(TimeType at) {
		bosses.reset(at);
		minions.reset(at);
		shots.reset(at);
		quips.reset(at);
	}
};

template<typename TimeType>
class WorldModel {
	ONLY_MOVE(WorldModel);
	AllAgents<TimeType> agents;
public:
	WorldModel() {}

	QuipP createQuip(const TimeType at, TrajectoryUniquePtr&& traj, std::string name);

	void reset(TimeType resetToTime) {
		agents.reset(resetToTime);
	}

	void forAllAgents(std::function<void(AgentP)> f, TimeType now) {
		agents.forEach(f, now);
	}
};
PTRS1(WorldModel, TimeType)

}
