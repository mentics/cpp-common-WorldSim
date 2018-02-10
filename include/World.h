#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

//using SchedPtr = Scheduler<RealTime>*;
//using SchedPtr = nn::nn<Scheduler<RealTime>*>;

class AgentControl;
using AgentControlUniquePtr = nn::nn<std::unique_ptr<AgentControl> >;

struct RealTimeProvider : public SchedulerTimeProvider<RealTime> {
	RealTime max = 2000000000000;
	RealTime lastChange = 0;
	double timeScale = 0; // Always start paused
	RealTime now();
	inline RealTime maxTimeAhead();
	inline chrono::nanoseconds realTimeUntil(RealTime t);
};
PTRS(RealTimeProvider)

class World {
public:
	World(RealTime userInputDelay);
	void setTimeScale(double newTimeScale);
	AgentControl createPlayerInput();
	RealTime userInputTimeToRun();
	AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

	std::pair<AgentControlUniquePtr, bool> getAgentControl(AgentId id);

private:
	RealTime userInputDelay;
	RealTimeProvider timeProv;
	SchedulerModel<RealTime,WorldModel> schedModel;
	Scheduler<RealTime,WorldModel> sched;
	WorldModel model;
};
