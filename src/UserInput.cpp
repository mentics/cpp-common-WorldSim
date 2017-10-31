#include "stdafx.h"
#include "UserInput.h"

void UserInput::tempAcc(const vect3& dir) {
	RealTime now = timeProv->now();
	sched->schedule(uniquePtr<EventAcc>(now, now + inputTimeDelay, agentId, dir));
}
