#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"
#include "Model.h"

namespace sched = mentics::scheduler;
namespace cmn = mentics::common;

typedef uint64_t RealTime; // nanoseconds

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

class World {
public:
	World(RealTime userInputDelay) : userInputDelay(userInputDelay), timeProvider(),
		schedModel("SchedulerModel"), sched("Scheduler", &schedModel, &timeProvider), model() {
	}

	void setTimeScale(double newTimeScale) {
		timeProvider.timeScale = newTimeScale;
		sched.wakeUp();
	}

	nn::nn<Agent*> createPlayer();

	RealTime userInputTimeToRun() {
		return timeProvider.now() + userInputDelay;
	}

	void addEvent(sched::Event<RealTime>* ev) {
		sched.schedule(ev);
	}

	AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

private:
	RealTime userInputDelay;
	RealTimeProvider timeProvider;
	sched::SchedulerModel<RealTime> schedModel;
	sched::Scheduler<RealTime> sched;
	Model model;
};

// TODO: export in dll
//World<RealTime>* startWorld();
//AgentId createPlayerInput(World<RealTime>* world);
