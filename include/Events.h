#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"
#include "World.h"

namespace MenticsGame {

class EventCreateQuip : public Event<WorldModel, RealTime>
{
	TrajectoryUniquePtr traj;
public:
	EventCreateQuip(const RealTime created, const RealTime timeToRun, TrajectoryUniquePtr&& initTraj) : Event(created, timeToRun), traj(std::move(initTraj)) {
	};

	void run(SchedulatorPtr<WorldModel, RealTime> sched, nn::nn<WorldModel*> model) override
	{
		model->createQuip(created, std::move(traj));
	}
};


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