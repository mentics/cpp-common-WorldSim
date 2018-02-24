#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Events.h"
#include "World.h"
#include "Scheduler.h"

namespace MenticsGame {
	// all agents, both human and AI, are limited to this class for controlling behavior
	class AgentControl {
	public:
		AgentControl(const AgentId agentId, const SchedulerPtr<WorldModel, RealTime> sched, const RealTimeProviderPtr timeProv)
			: agentId(agentId), sched(sched), timeProv(timeProv) {}

		void tempAcc(const vect3& dir);

	private:
		const AgentId agentId;
		const SchedulerPtr<WorldModel, RealTime> sched;
		const RealTimeProviderPtr timeProv;
	};
	PTRS(AgentControl);

}