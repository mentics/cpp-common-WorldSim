#include "stdafx-worldsim.h"
#include "World.h"
#include "AgentControl.h"
#include "Agent.h"
#include "TrajectoryCalculator.h"
#include "Events.h"

namespace MenticsGame {

void RealTimeProvider::setTimeScale(double newTimeScale) {
    lastChangeClock = currentTimeNanos();
    timeScale = newTimeScale;
}

RealTime RealTimeProvider::now() {
    RealTime nanos = (RealTime)((currentTimeNanos() - lastChangeClock) * timeScale);
    return nanos;
}

chrono::nanoseconds RealTimeProvider::realTimeUntil(RealTime toGameTime) {
    if (timeScale == 0) {
        return chrono::nanoseconds((RealTime)FOREVER);
    }
    RealTime toWait = toGameTime - now();
    double v = (double)toWait / timeScale;
    if (v > FOREVER || v < 0) {
        return chrono::nanoseconds((RealTime)FOREVER);
    } else {
        return chrono::nanoseconds((RealTime)v);
    }
}

void World::setTimeScale(double newTimeScale) {
    timeProv.setTimeScale(newTimeScale);
    sched.wakeUp();
}

AgentIndex World::allAgentsData(gsl::span<AgentPosVelAcc> buffer) {
    AgentIndex index = 0;
    const RealTime at = timeProv.now();
    model.forAllAgents([at, &buffer, &index](AgentPtr<RealTime, WorldModel<RealTime>> agent) {
        agent->trajectory.get(at)->posVelAcc(at, nn::nn_addr(buffer[index].pva));
        index++;
    }, at);
    return index;
}

void World::createQuip(RealTime afterDuration, TrajectoryUniquePtr<RealTime>&& traj, std::string name) {
    sched.schedule(afterDuration, uniquePtr<EventCreateQuip<RealTime>>(std::move(traj), name));
}

void World::takeControl(AgentPtr<RealTime, WorldModel<RealTime>> a) {
    // TODO: if there is some automated controller for agent, remote it
    // Otherwise, probably nothing to do
}

void World::consumeOutgoing(std::function<void(OutEventPtr<RealTime>)> handler, RealTime upToTime) {
    sched.consumeOutgoing(handler, upToTime);
}

}
