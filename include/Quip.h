#pragma once

#include "MenticsCommon.h"
#include "Signal.h"
#include "Agent.h"

namespace MenticsGame {

struct QuipHelper;
class QuipTest;

template<typename TimeType>
class Quip : public Agent<TimeType> {
	ONLY_MOVE(Quip);

public:
	const std::string name;
	SignalValue<float, TimeType> maxEnergy;			    // The current maximum energy this Quip can have.
	SignalValue<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
	SignalValue<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
	SignalValue<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.

	SignalValue<float, TimeType> energy;
	SignalValue<float, TimeType> attention;

	Quip(const AgentId id, TrajectoryUniquePtr&& trajectory,
			const float maxEnergy, const float energyRegenRate,
			const float maxAttention, const float attentionRegenRate,
			const std::string name, const TeamId team = 2)
				: Agent(id, std::move(trajectory), team), 
					maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention),
					attentionRegenRate(attentionRegenRate), energy(maxEnergy), attention(maxAttention), name(name) {}

	friend QuipHelper;
	friend QuipTest;

	void reset(TimeType resetTime) {
		Agent::reset(resetTime);
		maxEnergy.reset(resetTime);
		energyRegenRate.reset(resetTime);
		maxAttention.reset(resetTime);
		attentionRegenRate.reset(resetTime);
		energy.reset(resetTime);
		attention.reset(resetTime);
	}
};
PTRS1(Quip, TimeType)
#define QuipP QuipPtr<TimeType>
#define QuipUP QuipUniquePtr<TimeType>

}
