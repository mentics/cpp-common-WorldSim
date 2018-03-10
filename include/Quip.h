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
		//Quip(){}
		Quip(const AgentId id, UnqSignal<Trajectory, TimeType> trajectory,
			ValueSignal<double, TimeType> maxEnergy, ValueSignal<float, TimeType> energyRegenRate, ValueSignal<double, TimeType> maxAttention, ValueSignal<float, TimeType> attentionRegenRate, TeamId team = 2)
			: Agent(id, trajectory, team)
			, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
			, energy(maxEnergy), attention(maxAttention)
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
		ValueSignal<float, TimeType> maxEnergy;			// The current maximum energy this Quip can have.
		ValueSignal<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
		ValueSignal<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
		ValueSignal<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.
		
		ValueSignal<double, TimeType> energy;
		ValueSignal<double, TimeType> attention;
	};

}	