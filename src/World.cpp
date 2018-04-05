#include "stdafx.h"
#include <gsl/gsl>
#include "World.h"
#include "AgentControl.h"


namespace MenticsGame {
	//World<RealTime>* theWorld;
	//
	//World<RealTime>* startWorld() {
	//	theWorld = new World<RealTime>(100000000);
	//	return theWorld;
	//}

	void World::setTimeScale(double newTimeScale) {
		timeProv.setTimeScale(newTimeScale);
		sched.wakeUp();
	}
	

	RealTime World::userInputTimeToRun() {
		return timeProv.now() + userInputDelay;
	}

	RealTime  RealTimeProvider::now() {
		RealTime nanos = (currentTimeNanos() - lastChangeClock) * timeScale;
		return nanos;
	}

	AgentIndex World::allAgentsData(gsl::span<AgentPosVelAcc> buffer) {
		AgentIndex index = 0;
		const RealTime at = timeProv.now();
		model.agents.forEach([at, &buffer, &index](Agent<>* agent) {
			agent->trajectory.get((double)at)->posVelAcc(at, nn::nn_addr(buffer[index].pva));      
			index++;
		}, at);
		return index;
	}

	std::pair<AgentControlUniquePtr, bool> World::getAgentControl(AgentId id) {
		// TODO
		//if (model.agent(id)) {
		//	return std::make_pair(nn::nn_make_unique<AgentControl>(id, nn::nn_addr(sched), nn::nn_addr(timeProv)), true);
		//}
		//else {
			return std::make_pair(nn::nn_make_unique<AgentControl>(-1, nn::nn_addr(sched), nn::nn_addr(timeProv)), false);
		//}
	}

	void World::createQuip(RealTime at, TrajectoryUniquePtr&& traj)
	{
		sched.schedule(uniquePtr<EventCreateQuip>(getGameTime(), at, std::move(traj)));
	}

	WorldModel* getp(World *w)
	{
		return &w->model;
	}

	Scheduler<WorldModel, RealTime>* getpSched(World *w)
	{
		return &w->sched;
	}

	//AgentControl World::createPlayerInput() {
		//AgentId agentId = model.createAgent();
		//AgentControl input(agentId, nn::nn_addr(sched), nn::nn_addr(timeProv), userInputDelay);
		//return input;
	//}
}