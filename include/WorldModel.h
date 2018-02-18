#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Resettable.h"

namespace MenticsGame {
	typedef uint64_t RealTime; // nanoseconds

	class WorldModel;
	PTRS(WorldModel)

		struct Change2 {
		Change2(RealTime at) : at(at) {}

		virtual void apply(WorldModelPtr model) = 0;

		RealTime at;
	};
	PTRS(Change2)

		class WorldModel {
		public:
			Agent* agent(AgentId id) {
				return id < agents.size() ? &agents[id] : nullptr;
			}


			void reset(RealTime resetToTime);

		private:
			std::vector<Agent> agents;
			Resettable reset;
	};
}