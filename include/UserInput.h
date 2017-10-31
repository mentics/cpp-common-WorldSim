#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Events.h"
#include "World.h"

class UserInput {
public:
	UserInput(const AgentId agentId, const SchedPtr sched, const RealTimeProvPtr timeProv, RealTime inputTimeDelay)
		: agentId(agentId), sched(sched), timeProv(timeProv), inputTimeDelay(inputTimeDelay) {}

	void setTimeScale(double newTimeScale) {
		timeProv->timeScale = newTimeScale;
	}

	void tempAcc(const vect3& dir) {
		RealTime now = timeProv->now();
		sched->schedule(uniquePtr<EventAcc<RealTime>>(now, now + inputTimeDelay, agentId, dir));
	}

private:
	const AgentId agentId;
	const SchedPtr sched;
	const RealTimeProvPtr timeProv;
	RealTime inputTimeDelay;
};

