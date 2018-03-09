#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"
#include "World.h"

namespace MenticsGame {

class EventAcc : public Event<WorldModel, RealTime> {
public:
	EventAcc(const RealTime created, const RealTime timeToRun, const AgentId agentId, const vect3 dir) : Event(created, timeToRun), agentId(agentId), dir(dir) {
	};

	void run(SchedulatorPtr<WorldModel, RealTime> sched, nn::nn<WorldModel*> model) override;

private:
	const AgentId agentId;
	const vect3 dir;
};
PTRS(EventAcc)

}