#pragma once

#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

namespace MenticsGame {

typedef uint64_t RealTime; // nanoseconds

struct RealTimeProvider : public SchedulerTimeProvider<RealTime> {
	RealTime max = 2000000000000;
	RealTime lastChangeClock = 0;
	double timeScale = 0; // Always start paused

	RealTimeProvider() {
		lastChangeClock = currentTimeNanos();
	}

	void setTimeScale(RealTime newTimeScale) {
		lastChangeClock = currentTimeNanos();
		timeScale = newTimeScale;
	}

	RealTime now();

	inline chrono::nanoseconds realTimeUntil(RealTime toGameTime) {
		if (timeScale == 0) {
			return chrono::nanoseconds((RealTime)FOREVER);
		}
		RealTime toWait = toGameTime - now();
		double v = (double)toWait / timeScale;
		if (v > FOREVER || v < 0) {
			return chrono::nanoseconds((RealTime)FOREVER);
		}
		else {
			return chrono::nanoseconds((RealTime)v);
		}
	}
};

class World {
	ONLY_MOVE(World);

	RealTimeProvider timeProv;
	SchedulerModel<WorldModel<RealTime>, RealTime> schedModel;
	Scheduler<WorldModel<RealTime>, RealTime> sched;
	WorldModel<RealTime> model;

public:
	World(RealTime userInputDelay)
			: timeProv(), schedModel("SchedulerModel"),
			  sched("Scheduler", nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model)) {}

	void setTimeScale(double newTimeScale);

	AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

	RealTime getGameTime() { return timeProv.now(); }

	void createQuip(RealTime at, TrajectoryUniquePtr&& traj, std::string name);

	void takeControl(AgentPtr<TimePoint> a);

	void consumeOutgoing(std::function<void(OutEventPtr<RealTime>)> handler, RealTime upToTime);
};

}