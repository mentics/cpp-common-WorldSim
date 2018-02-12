#pragma once

#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Agent.h"
#include "Scheduler.h"
#include "World.h"


struct TrajectoryChange : public Change {
	TrajectoryChange(RealTime at, AgentId agentId, nn::nn_shared_ptr<Trajectory> newTraj, std::shared_ptr<Trajectory> newVisibleTraj)
		: Change{at}, agentId(agentId), newTraj(newTraj), newVisibleTraj(newVisibleTraj) {}

	void apply(WorldModelPtr model);

	AgentId agentId;
	nn::nn_shared_ptr<Trajectory> newTraj;
	std::shared_ptr<Trajectory> newVisibleTraj; // nullable because we don't set it if it's null
};


class EventAcc : public Event<RealTime,WorldModel> {
public:
	EventAcc(const RealTime created, const RealTime timeToRun, const AgentId agentId, const vect3 dir) : Event(created, timeToRun), agentId(agentId), dir(dir) {
	};

	void run(SchedulatorPtr<RealTime, WorldModel> sched, nn::nn<WorldModel*> model);

private:
	const AgentId agentId;
	const vect3 dir;
};