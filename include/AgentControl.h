#pragma once
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

namespace MenticsGame {

////
// all agents, both human and AI, are limited to this class for controlling behavior
template<typename TimeType>
class AgentControl {
	TimeType inputDelay;
	const AgentWP agent;
	const SchedulatorWP sched;

public:
	AgentControl(const TimeType inputDelay, const AgentWP agent, const SchedulatorWP sched)
		: inputDelay(inputDelay), agent(agent), sched(sched) {}

	void arrive(const AgentWP agent, const AgentWP target, const double distance);

	void tempAcc(const vect3& dir);
};
PTRS1(AgentControl, TimeType)
#define AgentControlP AgentControlPtr<TimeType>
#define AgentControlUP AgentControlUniquePtr<TimeType>

}