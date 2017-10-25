#include "stdafx.h"
#include "World.h"

World<RealTime>* theWorld;

World<RealTime>* startWorld() {
	theWorld = new World<RealTime>(100000000);
	return theWorld;
}

AgentId createPlayerInput(World<RealTime>* world) {
	// TODO
	return 0;
}