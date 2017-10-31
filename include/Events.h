#pragma once

#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"

template <typename TimeType, typename Model>
class EventAcc : public Event<TimeType,Model> {
public:
	EventAcc(const TimeType created, const TimeType timeToRun, const AgentId agentId, const vect3 dir) : Event(created, timeToRun), agentId(agentId), dir(dir) {
	};

	void run(SchedulatorPtr<TimeType,Model> sched, nn::nn<Model*> model);

private:
	const AgentId agentId;
	const vect3 dir;
};