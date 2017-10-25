#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"

namespace sched = mentics::scheduler;
namespace cmn = mentics::common;

typedef uint64_t RealTime; // nanoseconds

struct RealTimeProvider : public sched::SchedulerTimeProvider<RealTime> {
	RealTime max = 2000000000;
	RealTime lastChange = 0;
	double timeScale = 1;

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
		return (RealTime)((t - now) / timeScale);
	}
};

template <typename TimeType>
class World {
public:
	World(TimeType userInputDelay) : userInputDelay(userInputDelay), timeProvider(),
		model("SchedulerModel"), sched("Scheduler", &model, &timeProvider) {
	}

	AgentId createPlayerInput();

	TimeType userInputTimeToRun() {
		return timeProvider.now() + userInputDelay;
	}

	void addEvent(sched::Event<TimeType>* ev) {
		sched.schedule(ev);
	}

private:
	TimeType userInputDelay;
	RealTimeProvider timeProvider;
	sched::SchedulerModel<RealTime> model;
	sched::Scheduler<RealTime> sched;
};

// TODO: export in dll
World<RealTime>* startWorld();
AgentId createPlayerInput(World<RealTime>* world);