#include "stdafx-worldsim.h"
#include "Events.h"
#include "World.h"

#include "SchedulerModel.cpp"
#include "Scheduler.cpp"
#include "Events.cpp"
#include "WorldModel.cpp"

namespace MenticsGame {

template WorldModel<RealTime>;
template Scheduler<RealTime, WorldModel<RealTime>>;
template EventCreateQuip<RealTime>;

}
