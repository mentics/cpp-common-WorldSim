#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "Events.hpp"

//World<RealTime>* theWorld;
//
//World<RealTime>* startWorld() {
//	theWorld = new World<RealTime>(100000000);
//	return theWorld;
//}

AgentIndex World::allAgentsData(gsl::span<AgentPosVelAcc> buffer) {
	AgentIndex index = 0;
	const RealTime at = timeProvider.now();
	model.forAllAgents(buffer.length(), [at, &buffer, &index](const Agent& agent) {
		agent.trajectory->posVelAcc((double)at, &(buffer[index].pva));
		index++;
	});
	return index;
}

nn::nn<Agent*> World::createPlayer() {
	return model.createAgent();
}