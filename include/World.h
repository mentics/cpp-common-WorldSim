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

	RealTime now() {
		RealTime nanos = currentTimeNanos();
		RealTime millis = currentTimeMillis();
		return nanos;
	}

	inline RealTime maxTimeAhead() {
		return max;
	}

	inline chrono::nanoseconds realTimeUntil(RealTime t) {
		if (timeScale == 0) {
			return chrono::nanoseconds((RealTime)FOREVER);
		}
		RealTime now = currentTimeNanos();
		return chrono::nanoseconds((RealTime)trunc((t - now) / timeScale));
	}
};
PTRS(RealTimeProvider)

class World {
public:
	World(RealTime userInputDelay) : userInputDelay(userInputDelay), timeProv(),
		model(), schedModel("SchedulerModel"), sched("Scheduler", nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model)) {
	}

	void setTimeScale(double newTimeScale) {
		timeProv.timeScale = newTimeScale;
		sched.wakeUp();
	}

	AgentControl createPlayerInput();

	RealTime userInputTimeToRun() {
		return timeProv.now() + userInputDelay;
	}

	AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

	std::pair<AgentControlUniquePtr, bool> getAgentControl(AgentId id);

private:
	RealTime userInputDelay;
	RealTimeProvider timeProv;
	SchedulerModel<RealTime,WorldModel> schedModel;
	Scheduler<RealTime,WorldModel> sched;
	WorldModel model;
};
