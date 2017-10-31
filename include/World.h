#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"


typedef uint64_t RealTime; // nanoseconds

//using SchedPtr = sched::Scheduler<RealTime>*;
//using SchedPtr = nn::nn<sched::Scheduler<RealTime>*>;

class UserInput;

struct RealTimeProvider : public sched::SchedulerTimeProvider<RealTime> {
	RealTime max = 2000000000;
	RealTime lastChange = 0;
	double timeScale = 0; // Always start paused

	virtual RealTime now() {
		return cmn::currentTimeNanos();
	}

	inline RealTime maxTimeAhead() {
		return max;
	}

	inline RealTime realTimeUntil(RealTime t) {
		if (timeScale == 0) {
			return FOREVER;
		}
		RealTime now = cmn::currentTimeNanos();
		return trunc((t - now) / timeScale);
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

	UserInput createPlayerInput();

	RealTime userInputTimeToRun() {
		return timeProv.now() + userInputDelay;
	}

	AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

private:
	RealTime userInputDelay;
	RealTimeProvider timeProv;
	sched::SchedulerModel<RealTime,WorldModel> schedModel;
	sched::Scheduler<RealTime,WorldModel> sched;
	WorldModel model;
};
