#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Resettable.h"


namespace MenticsGame {
	typedef uint64_t RealTime; // nanoseconds

	class WorldModel;
	PTRS(WorldModel)


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