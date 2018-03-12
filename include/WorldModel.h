#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Quip.h"
#include "Signal.h"



namespace MenticsGame {
	typedef uint64_t RealTime; // nanoseconds

	class WorldModel;
	PTRS(WorldModel)

	struct AllAgents
	{
		ONLY_MOVE(AllAgents);
	public:
		SignalCollection<Boss, RealTime> bosses;
		SignalCollection<Minion, RealTime> minions;  
		SignalCollection<Shot, RealTime> shots;
		SignalCollection<Quip<RealTime>, RealTime> quips;

		AllAgents() {}

		template <typename TimeType = TimePoint>
		void forEach(std::function<void(Agent<>*)> f, TimeType now)
		{
			bosses.forEach(now, f );
			minions.forEach(now,f);
			shots.forEach(now, f);
			quips.forEach(now, f);
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
		WorldModel() {}

		void createQuip(RealTime at); 

		void reset(RealTime resetToTime) {
			agents.reset(resetToTime);
		}
		
		AllAgents agents;
	private:
		ONLY_MOVE(WorldModel);
	};

	
}