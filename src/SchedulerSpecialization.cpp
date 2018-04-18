#include "stdafx.h"
#include "Events.h"
#include "World.h"

#include "Scheduler.cpp"
#include "Events.cpp"
#include "WorldModel.cpp"


namespace MenticsGame {

//void justToForceTemplateSpecializationSoIgnore() {
	//World w;
	//WorldModel<RealTime> model;
	//model.createQuip(0, makeTrajRandom(0,0,0), "name");
	//RealTimeProvider timeProv;
	//SchedulerModel<WorldModel<RealTime>, RealTime> schedModel;
	//schedModel.consumeOutgoing(nullptr, 0);
	//Scheduler<WorldModel<RealTime>, RealTime> sched(nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model));
	//sched.schedule(0, uniquePtr<CmdAcc<RealTime>>(Minion<RealTime>(), vect3()));
	//w.createQuip(0, makeTrajZero(), "name");
//}

template WorldModel<RealTime>;
template Scheduler<WorldModel<RealTime>, RealTime>;
template EventCreateQuip<RealTime>;

}