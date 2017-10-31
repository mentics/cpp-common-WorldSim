#include "stdafx.h"
#include "Events.hpp" // Only place this should be included
#include "UserInput.h"

void UserInput::tempAcc(const vect3& dir) {
	RealTime now = timeProv->now();
	sched->schedule(uniquePtr<EventAcc<RealTime,WorldModel>>(now, now + inputTimeDelay, agentId, dir));
}
