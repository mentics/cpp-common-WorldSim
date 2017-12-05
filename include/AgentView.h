#pragma once

#include "World.h"

// Each agent has a limited and delayed perception of the world. 
// This AgentView is how AI agents and automated behaviors for human players 
// perceive the game world. In other words, any Agent behavior that requires 
// a value for calculation/consideration must get it from its AgentView.
class AgentView {
public:
	AgentView(WorldModelPtr worldModel) : worldModel(worldModel)
	{}
protected:
	WorldModelPtr worldModel;
};