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
		Quip(){}
		Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory,
			float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, TeamId team = 2)
			: Agent(id, trajectory, team)
			, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
			, energy(maxEnergy, 0), attention(maxAttention, 0)
		{
			maxEnergy.add(0, 0);
			energyRegenRate.add(0, 0);
			maxAttention.add(0, 0);
			attentionRegenRate.add(0, 0);
			energy.add(0, 0);
			attention.add(0, 0);
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
		Signal<float, TimeType> maxEnergy;			// The current maximum energy this Quip can have.
		Signal<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
		Signal<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
		Signal<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.

		Signal<double, TimeType> energy;
		Signal<double, TimeType> attention;
	};

}	