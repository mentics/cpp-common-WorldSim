#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Events.h"
#include "World.h"

using namespace mentics::scheduler;

class UserInput {
public:
	UserInput(const AgentId agentId, const SchedulerPtr<RealTime,WorldModel> sched, const RealTimeProviderPtr timeProv, RealTime inputTimeDelay)
		: agentId(agentId), sched(sched), timeProv(timeProv), inputTimeDelay(inputTimeDelay) {}

	void setTimeScale(double newTimeScale) {
		timeProv->timeScale = newTimeScale;
	}

	void tempAcc(const vect3& dir);

private:
	const AgentId agentId;
	const SchedulerPtr<RealTime, WorldModel> sched;
	const RealTimeProviderPtr timeProv;
	RealTime inputTimeDelay;
};

