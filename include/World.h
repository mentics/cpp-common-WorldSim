#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"
#include "Model.h"


typedef uint64_t RealTime; // nanoseconds
using SchedPtr = sched::Scheduler<RealTime>*;
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
			return sched::FOREVER<RealTime>();
		}
		RealTime now = cmn::currentTimeNanos();
		return trunc((t - now) / timeScale);
	}
};
using RealTimeProvPtr = RealTimeProvider*;
//using RealTimeProvPtr = nn::nn<RealTimeProvider*>;

class World {
public:
	World(RealTime userInputDelay) : userInputDelay(userInputDelay), timeProv(),
		schedModel("SchedulerModel"), sched("Scheduler", &schedModel, &timeProv), model() {
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
	sched::SchedulerModel<RealTime> schedModel;
	sched::Scheduler<RealTime> sched;
	Model model;
};
