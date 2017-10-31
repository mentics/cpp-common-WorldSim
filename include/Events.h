#pragma once

#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"


template <typename TimeType>
class EventAcc : public sched::Event<TimeType> {
public:
	EventAcc(const TimeType created, const TimeType timeToRun, const AgentId agentId, const vect3 dir) : Event(created, timeToRun), agentId(agentId), dir(dir) {
	};

	void run(sched::Schedulator<TimeType>* sched);

private:
	const AgentId agentId;
	const vect3 dir;
};