#pragma once

#include "Agent.h"
#include "Quip.h"
#include "Signal.h"

namespace MenticsGame {

#define QuipWP QuipPtr<TimeType, WorldModel<TimeType>>
#define AgentWP AgentPtr<TimeType,WorldModel<TimeType>>
#define SchedulatorWP SchedulatorPtr<TimeType,WorldModel<TimeType>>


template<typename TimeType, typename Model>
struct AllAgents {
	ONLY_MOVE(AllAgents);
public:
	SignalCollection<Boss<TimeType,Model>, TimeType> bosses;
	SignalCollection<Minion<TimeType,Model>, TimeType> minions;
	SignalCollection<Shot<TimeType,Model>, TimeType> shots;
	SignalCollection<Quip<TimeType,Model>, TimeType> quips;

	AllAgents() {}

	void forEach(std::function<void(AgentP)> f, TimeType now) {
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
	typedef WorldModel Model;
	ONLY_MOVE(WorldModel);
	AllAgents<TimeType,WorldModel> agents;
public:
	WorldModel() {}

	QuipWP createQuip(const TimeType at, TrajectoryUniquePtr&& traj, std::string name);

	void reset(TimeType resetToTime) {
		agents.reset(resetToTime);
	}

	void forAllAgents(std::function<void(AgentP)> f, TimeType now) {
		agents.forEach(f, now);
	}
};
PTRS1(WorldModel, TimeType)
#define WorldModelP WorldModelPtr<TimeType>
#define WorldModelUP WorldModelUniquePtr<TimeType>

}
