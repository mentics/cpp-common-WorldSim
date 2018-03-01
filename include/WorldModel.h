#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Resettable.h"
#include "Quip.h"

class Quip;

namespace MenticsGame {
	typedef uint64_t RealTime; // nanoseconds

	class WorldModel;
	PTRS(WorldModel)

	struct AllAgents
	{
		std::vector<Boss> bosses;
		std::vector<Minion> minions;
		std::vector<Shot> shots;
		std::vector<Quip<RealTime>> quips;

		template <typename T>
		void forEach(T f)
		{
			for (Boss boss : bosses) f(boss);
			for (Minion minion : minions) f(minion);
			for (Shot shot : shots) f(shot);
			for (Quip<RealTime> quip : quips) f(quip);
		}

		size_t size()
		{
			return bosses.size() + minions.size() + shots.size();// + quips.size();
		}

	};

	class WorldModel {
	public:
		Agent<RealTime>* agent(AgentId id) {
			//return id < agents.size() ? &agents[id] : nullptr;
			return nullptr;
		}


		void reset(RealTime resetToTime);


		
		AllAgents agents;
	private:
		Resettable<RealTime> Reset;
	};
}