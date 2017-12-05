#pragma once

#include "Signal.h"

class Quip {
public:
	Quip(float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate);
private:
	float maxEnergy;			// The current maximum energy this Quip can have.
	float energyRegenRate;		// The current rate at which this Quip regenerates energy.
	float maxAttention;			// The current maximum attention this Quip can have.
	float attentionRegenRate;	// The current rate at which this Quip regenerates attention.

	Signal<double> energy; 
	Signal<double> attention;
};