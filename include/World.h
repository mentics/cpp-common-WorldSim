#pragma once
#include "MenticsCommon.h"
#include "Scheduler.h"


namespace sched = mentics::scheduler;
namespace cmn = mentics::common;

typedef uint64_t RealTime; // nanoseconds

struct RealTimeProvider : public sched::SchedulerTimeProvider<RealTime> {
	RealTime max = 2000000000;
	RealTime lastChange = 0;
	double timeScale = 1;

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


class World {
public:
	World() : timeProvider(), model("SchedulerModel"), sched("Scheduler", &model, &timeProvider) {
	}

	void start() {
		// TODO: sched.run...
	}

private:
	RealTimeProvider timeProvider;
	sched::SchedulerModel<RealTime> model;
	sched::Scheduler<RealTime> sched;
};