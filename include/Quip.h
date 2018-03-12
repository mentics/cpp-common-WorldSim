#pragma once

#include "Signal.h"
#include "Agent.h"
#include "Resettable.h"


namespace MenticsGame {
	struct QuipHelper;
	class QuipTest;

	template<typename TimeType = TimePoint>
	class Quip : public Agent<TimeType> {
	public:
		Quip(const AgentId id, TrajectoryUniquePtr&& trajectory,
				float maxEnergy, float energyRegenRate,
				float maxAttention, float attentionRegenRate,
				TeamId team = 2)
					: Agent(id, std::move(trajectory), team),
						maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention),
						attentionRegenRate(attentionRegenRate), energy(maxEnergy), attention(maxAttention)
		{
			
		}

		friend QuipHelper;
		friend QuipTest;

		void reset(TimeType resetTime)
		{
			Agent::reset(resetTime);
			maxEnergy.reset(resetTime);
			energyRegenRate.reset(resetTime);
			maxAttention.reset(resetTime);
			attentionRegenRate.reset(resetTime);
			energy.reset(resetTime);
			attention.reset(resetTime);
		}
	private:
		ONLY_MOVE(Quip);

		SignalValue<float, TimeType> maxEnergy;			// The current maximum energy this Quip can have.
		SignalValue<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
		SignalValue<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
		SignalValue<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.
		
		SignalValue<float, TimeType> energy;
		SignalValue<float, TimeType> attention;
	};

}	