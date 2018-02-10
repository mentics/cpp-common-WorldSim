#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "AgentControl.h"
#include "Scheduler.cpp" // This should be the only place that includes this

//World<RealTime>* theWorld;
//
//World<RealTime>* startWorld() {
//	theWorld = new World<RealTime>(100000000);
//	return theWorld;
//}

AgentIndex World::allAgentsData(gsl::span<AgentPosVelAcc> buffer) {
	AgentIndex index = 0;
	const RealTime at = timeProv.now();
	model.forAllAgents(buffer.length(), [at, &buffer, &index](const Agent& agent) {
		agent.trajectory->posVelAcc((double)at, nn::nn_addr(buffer[index].pva));
		index++;
	});
	return index;
}

std::pair<AgentControlUniquePtr, bool> World::getAgentControl(AgentId id) {
	if (model.agent(id)) {
		return std::make_pair(nn::nn_make_unique<AgentControl>(id, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay), true);
	}
	else {
		return std::make_pair(nn::nn_make_unique<AgentControl>(-1, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay), false);
	}

}

AgentControl World::createPlayerInput() {
	AgentId agentId = model.createAgent();
	AgentControl input(agentId, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
	return input;
}


RealTime RealTimeProvider::now() {
	RealTime nanos = currentTimeNanos();
	RealTime millis = currentTimeMillis();
	return nanos;
}

RealTime RealTimeProvider::maxTimeAhead() {
	return max;
}

chrono::nanoseconds RealTimeProvider::realTimeUntil(RealTime t) {
	if (timeScale == 0) {
		return chrono::nanoseconds((RealTime)FOREVER);
	}
	RealTime now = currentTimeNanos();
	return chrono::nanoseconds((RealTime)trunc((t - now) / timeScale));
}

World::World(RealTime userInputDelay) : userInputDelay(userInputDelay), timeProv(),
model(), schedModel("SchedulerModel"), sched("Scheduler", nn::nn_addr(schedModel), nn::nn_addr(timeProv), nn::nn_addr(model)) {}

void World::setTimeScale(double newTimeScale) {
	timeProv.timeScale = newTimeScale;
	sched.wakeUp();
}

RealTime World::userInputTimeToRun() {
	return timeProv.now() + userInputDelay;
}