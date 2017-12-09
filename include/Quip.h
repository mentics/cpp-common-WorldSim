#pragma once

#include "Signal.h"
#include "Agent.h"

class Quip : public Agent {
public:
	Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, uint16_t team = 2);
private:
	float maxEnergy;			// The current maximum energy this Quip can have.
	float energyRegenRate;		// The current rate at which this Quip regenerates energy.
	float maxAttention;			// The current maximum attention this Quip can have.
	float attentionRegenRate;	// The current rate at which this Quip regenerates attention.

	Signal<double> energy; 
	Signal<double> attention;
};