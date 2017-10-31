#include "stdafx.h"

#include "Events.h"

void EventAcc::run(SchedulatorPtr<RealTime,WorldModel> sched, nn::nn<WorldModel*> model) {
	const RealTime LONG_ENOUGH = 50000000; // TODO: how long?
	Agent* a = model->agent(agentId);
	Trajectory& curTraj = *a->trajectory;
	std::shared_ptr<Trajectory> visible;
	if (a->trajectory->startTime < (timeToRun - LONG_ENOUGH)) {
		visible = a->trajectory;
	}
	vect3 pos;
	vect3 vel;
	curTraj.posVel(timeToRun, pos, vel);
	nn::nn_shared_ptr<Trajectory> newTraj = nn::nn_make_shared<BasicTrajectory>(timeToRun, FOREVER, pos, vel, dir);
	model->change(uniquePtrC<Change, TrajectoryChange>(timeToRun, agentId, newTraj, visible));
}

