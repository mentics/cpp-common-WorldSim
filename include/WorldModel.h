#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
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
			AgentId createAgent() {
				agents.emplace_back(agents.size(), makeTrajZero(), makeTrajZero());
				return agents.back().id;
			}

			void forAllAgents(AgentIndex max, std::function<void(const Agent&)> handler);

			Agent* agent(AgentId id) {
				return id < agents.size() ? &agents[id] : nullptr;
			}

			void change(Change2UniquePtr c);

			void reset(RealTime resetToTime);

		private:
			std::vector<Agent> agents;
	};
}