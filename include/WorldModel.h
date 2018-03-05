#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Resettable.h"
#include "Quip.h"
#include "Signal.h"



namespace MenticsGame {
	typedef uint64_t RealTime; // nanoseconds

	class WorldModel;
	PTRS(WorldModel)

	struct AllAgents
	{ 
		SignalCollection<Boss, RealTime> bosses;
		SignalCollection<Minion, RealTime> minions;  
		SignalCollection<Shot, RealTime> shots;
		SignalCollection<Quip<RealTime>, RealTime> quips;

		template <typename TimeType = TimePoint>
		void forEach(std::function<void(Agent<>*)> f, TimeType now)
		{
			bosses.forEach(now, [=](Boss* b) {f(b); });
			minions.forEach(now, [=](Minion* b) {f(b); });
			shots.forEach(now, [=](Shot* b) {f(b); });
			quips.forEach(now, [=](Quip* b) {f(b); });                     
		}

		void reset(RealTime at)
		{
			bosses.reset(at);
			minions.reset(at);
			shots.reset(at);
			quips.reset(at);
		}

	};

	class WorldModel {
	public:
		Agent<RealTime>* agent(AgentId id) {
			//return id < agents.size() ? &agents[id] : nullptr; // need size() for this 
			return nullptr;
		}


		void reset(RealTime resetToTime);


		
		AllAgents agents;
	private:
	};
}