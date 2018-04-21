#pragma once
#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Agent.h"
#include "EventBases.h"
#include "WorldModel.h"

namespace MenticsGame {

template<typename TimeType>
class EventCreateQuip : public Event<TimeType,WorldModel<TimeType>> {
	TrajectoryUniquePtr traj;
	const std::string name;

public:
	EventCreateQuip(TrajectoryUniquePtr&& initTraj, std::string name) : traj(std::move(initTraj)), name(name) {}

	void run(SchedulatorWP sched, nn::nn<WorldModel<TimeType>*> model) override;
};

template<typename TimeType>
class CmdArrive : public Event<TimeType,WorldModel<TimeType>> {
	AgentWP agent;
	AgentWP target;
	double dist;

public:
	CmdArrive(AgentWP agent, AgentWP target, double dist) : agent(agent), target(target), dist(dist) {}

	void run(SchedulatorWP sched, nn::nn<WorldModel<TimeType>*> model) override;
};

template<typename TimeType>
class CmdAcc : public Event<TimeType,WorldModel<TimeType>> {
	const AgentWP agent;
	const vect3 dir;

public:
	CmdAcc(const AgentWP agent, const vect3 dir) : agent(agent), dir(dir) {}
	void run(SchedulatorWP sched, nn::nn<WorldModel<TimeType>*> model) override;
};

}
