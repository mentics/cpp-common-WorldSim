#include "stdafx.h"
#include "Scheduler.cpp"
#include "World.h"

namespace MenticsGame {

void justToForceTemplateSpecializationSoIgnore() {
	WorldModel model;
	RealTimeProvider timeProv;
	SchedulerModel<WorldModel, RealTime> schedModel("");
	Scheduler<WorldModel, RealTime> sched("Scheduler", nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model));
	sched.schedule(uniquePtr<EventAcc>(0, 0, 0, vect3()));
}

}