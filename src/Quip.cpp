#include "stdafx.h"
#include "Quip.h"
#include "SignalFunctions.h"

Quip::Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, 
	float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, uint16_t team)
	: Agent(id, trajectory, visibleTrajectory, team)
	, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
, energy(SignalFunctions::ConstantFunction<double>(maxEnergy)), attention(SignalFunctions::ConstantFunction<double>(maxAttention))
{}
