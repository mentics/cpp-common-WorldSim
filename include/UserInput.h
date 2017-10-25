#pragma once

#include "Agent.h"
#include "MenticsMath.h"
#include "World.h"
#include "Events.h"

void tempAcc(World<RealTime>* world, AgentId agentId, vect3 dir) {
	world->addEvent(new EventAcc<RealTime>(world->userInputTimeToRun(), dir));
}