#include "stdafx.h"
#include "AgentControl.h"

void AgentControl::tempAcc(const vect3& dir) {
	RealTime now = timeProv->now();
	sched->schedule(uniquePtr<EventAcc>(now, now + inputTimeDelay, agentId, dir));
}


void AgentControl::setTimeScale(double newTimeScale) {
	timeProv->timeScale = newTimeScale;
}

