#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "AgentControl.h"
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
		agent.trajectory->posVelAcc((double)at, nn::nn_addr(buffer[index].pva));
		index++;
	});
	return index;
}

nn::nn_unique_ptr<AgentControl> World::getControlAgent(AgentId id) {
	return nn::nn_make_unique<AgentControl>(id, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
}

//AgentControlUniquePtr World::getAgentControl(AgentId id) {
//	return nn::nn_make_unique<AgentControl>(id, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
//}

AgentControl World::createPlayerInput() {
	AgentId agentId = model.createAgent();
	AgentControl input(agentId, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
	return input;
}