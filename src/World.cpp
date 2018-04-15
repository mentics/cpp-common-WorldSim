#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "AgentControl.h"
#include "Scheduler.cpp"
#include "Agent.h"
#include "TrajectoryCalculator.h"
#include "Events.h"

namespace MenticsGame {

RealTime  RealTimeProvider::now() {
	RealTime nanos = (currentTimeNanos() - lastChangeClock) * timeScale;
	return nanos;
}

void World::setTimeScale(double newTimeScale) {
	timeProv.setTimeScale(newTimeScale);
	sched.wakeUp();
}

AgentIndex World::allAgentsData(gsl::span<AgentPosVelAcc> buffer) {
	AgentIndex index = 0;
	const RealTime at = timeProv.now();
	model.forAllAgents([at, &buffer, &index](AgentPtr<RealTime> agent) {
		agent->trajectory.get((double)at)->posVelAcc(at, nn::nn_addr(buffer[index].pva));      
		index++;
	}, at);
	return index;
}

void World::createQuip(RealTime at, TrajectoryUniquePtr&& traj, std::string name) {
	sched.schedule(uniquePtr<EventCreateQuip<RealTime>>(std::move(traj), name)); 
}

void World::takeControl(AgentPtr<TimePoint> a) {
	// TODO: if there is some automated controller for agent, remote it
	// Otherwise, probably nothing to do
}

void World::consumeOutgoing(std::function<void(OutEventPtr<RealTime>)> handler, RealTime upToTime) {
	sched.getSchedModel()->consumeOutgoing(handler, upToTime);
		
}

}