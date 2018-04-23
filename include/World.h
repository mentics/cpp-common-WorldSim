#pragma once
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"

namespace MenticsGame {

typedef uint64_t RealTime; // nanoseconds

class RealTimeProvider : public SchedulerTimeProvider<RealTime> {
    RealTime max = 2000000000000;
    RealTime lastChangeClock = 0;
    double timeScale = 0; // Always start paused

public:
    RealTimeProvider() {
        lastChangeClock = currentTimeNanos();
    }
    void setTimeScale(double newTimeScale);
    RealTime now();
    chrono::nanoseconds realTimeUntil(RealTime toGameTime);
};

class World {
    ONLY_MOVE(World);

    RealTimeProvider timeProv;
    SchedulerModel<RealTime, WorldModel<RealTime>> schedModel;
    Scheduler<RealTime, WorldModel<RealTime>> sched;
    WorldModel<RealTime> model;

public:
    World() : timeProv(), schedModel(), sched(nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model)) {}

    void setTimeScale(double newTimeScale);
    RealTime getGameTime() {
        return timeProv.now();
    }
    AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

    void consumeOutgoing(std::function<void(OutEventPtr<RealTime>)> handler, RealTime upToTime);

    void takeControl(AgentPtr<RealTime, WorldModel<RealTime>> a);

    void createQuip(RealTime at, TrajectoryUniquePtr&& traj, std::string name);
};

}
