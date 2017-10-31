#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "UserInput.h"
#include "Events.hpp" // This should be the only place that includes this
#include "Scheduler.hpp" // This should be the only place that includes this

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
		agent.trajectory->posVelAcc((double)at, &(buffer[index].pva));
		index++;
	});
	return index;
}

UserInput World::createPlayerInput() {
	AgentPtr agent = model.createAgent();
	UserInput input(agent->id, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
	return input;
}