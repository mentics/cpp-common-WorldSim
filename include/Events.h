#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

namespace MenticsGame {

template<typename TimeType>
class EventCreateQuip : public Event<WorldModel<TimeType>, TimeType> {
	TrajectoryUniquePtr traj;
	const std::string name;

public:
	EventCreateQuip(TrajectoryUniquePtr&& initTraj, std::string name) : traj(std::move(initTraj)), name(name) {}

	void run(SchedulatorPtr<WorldModel<TimeType>, TimeType> sched, nn::nn<WorldModel<TimeType>*> model) override;
};

template<typename TimeType>
class CmdArrive : public Event<WorldModel<TimeType>, TimeType> {
	AgentPtr<TimeType> agent;
	AgentPtr<TimeType> target;
	double dist;

public:
	CmdArrive(AgentPtr<TimeType> agent, AgentPtr<TimeType> target, double dist) : agent(agent), target(target), dist(dist) {}

	void run(SchedulatorPtr<WorldModel<TimeType>, TimeType> sched, nn::nn<WorldModel<TimeType>*> model) override;
};

template<typename TimeType>
class CmdAcc : public Event<WorldModel<TimeType>, TimeType> {
	const AgentPtr<TimeType> agent;
	const vect3 dir;

public:
	CmdAcc(const AgentPtr<TimeType> agent, const vect3 dir) : agent(agent), dir(dir) {}
	void run(SchedulatorPtr<WorldModel<TimeType>, TimeType> sched, nn::nn<WorldModel<TimeType>*> model) override;
};

}
