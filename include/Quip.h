#pragma once

#include "MenticsCommon.h"
#include "Signal.h"
#include "Agent.h"

namespace MenticsGame {

PTRS2(Quip, TimeType, Model)
#define QuipP QuipPtr<TimeType,Model>
#define QuipUP QuipUniquePtr<TimeType,Model>
template<typename TimeType, typename Model>
class Quip : public Agent<TimeType,Model> {
	ONLY_MOVE(Quip);

public:
	const std::string name;
	SignalValue<float, TimeType> maxEnergy;			    // The current maximum energy this Quip can have.
	SignalValue<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
	SignalValue<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
	SignalValue<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.

	SignalValue<float, TimeType> energy;
	SignalValue<float, TimeType> attention;

	Quip(const AgentId id, TimeType createTime, TrajectoryUniquePtr<TimeType>&& trajectory,
			const float maxEnergy, const float energyRegenRate,
			const float maxAttention, const float attentionRegenRate,
			const std::string name, const TeamId team = 2)
				: Agent(id, createTime, std::move(trajectory), team),
					maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention),
					attentionRegenRate(attentionRegenRate), energy(maxEnergy), attention(maxAttention), name(name) {}

	static QuipUP createDefault(const AgentId id) {
		return uniquePtr<Quip<TimeType,Model>>(id, makeTrajZero(), 0, 0, 0, 0, "QuipDefault");
	}

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

}
