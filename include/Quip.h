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
		Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory,
			float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, TeamId team = 2)
			: Agent(id, trajectory, visibleTrajectory, team)
			, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
			, energy(maxEnergy, 0), attention(maxAttention, 0)
		{}
		friend QuipHelper;
		friend QuipTest;

	private:
		Signal<float, TimeType> maxEnergy;			// The current maximum energy this Quip can have.
		Signal<float, TimeType> energyRegenRate;		// The current rate at which this Quip regenerates energy.
		Signal<float, TimeType> maxAttention;			// The current maximum attention this Quip can have.
		Signal<float, TimeType> attentionRegenRate;	// The current rate at which this Quip regenerates attention.

		Signal<double, TimeType> energy;
		Signal<double, TimeType> attention;
	};

}	