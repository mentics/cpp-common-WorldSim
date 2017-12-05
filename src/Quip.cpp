#include "stdafx.h"
#include "Quip.h"
#include "SignalFunctions.h"

Quip::Quip(float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate)
: maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
, energy(SignalFunctions::ConstantFunction<double>(maxEnergy)), attention(SignalFunctions::ConstantFunction<double>(maxAttention))
{}
