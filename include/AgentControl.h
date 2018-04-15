#pragma once

#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

namespace MenticsGame {

// all agents, both human and AI, are limited to this class for controlling behavior
template<typename TimeType>
class AgentControl {
	TimeType inputDelay;
	const AgentP agent;
	const SchedulerPtr<WorldModel<TimeType>, TimeType> sched;

public:
	AgentControl(const TimeType inputDelay, const AgentP agent, const SchedulerPtr<WorldModel<TimeType>, TimeType> sched)
		: inputDelay(inputDelay), agent(agent), sched(sched) {}

	void arrive(const AgentP agent, const AgentP target, const double distance);

	void tempAcc(const vect3& dir);
};
PTRS1(AgentControl, TimeType)
#define AgentControlP AgentControlPtr<TimeType>
#define AgentControlUP AgentControlUniquePtr<TimeType>

}