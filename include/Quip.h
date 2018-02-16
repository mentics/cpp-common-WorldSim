#pragma once

#include "WorldModel.h"
#include "Signal.h"
#include "Agent.h"
#include "Resettable.h"

namespace MenticsGame {
	struct QuipHelper;
	class QuipTest;

	class Quip : public Agent {
	public:
		Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, uint16_t team = 2);
		friend QuipHelper;
		friend QuipTest;

	private:
		float maxEnergy;			// The current maximum energy this Quip can have.
		float energyRegenRate;		// The current rate at which this Quip regenerates energy.
		float maxAttention;			// The current maximum attention this Quip can have.
		float attentionRegenRate;	// The current rate at which this Quip regenerates attention.

		Signal<double> energy;
		Signal<double> attention;
	};

	using QuipChange = Change<Quip, RealTime>;


	struct QuipHelper {
		static QuipChange createQuipChange(float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate);
		static std::function<QuipChange(float)> createMaxEnergyChange;
		static std::function<QuipChange(float)> createEnergyRegenRateChange;
		static std::function<QuipChange(float)> createMaxAttentionChange;
		static std::function<QuipChange(float)> createAttentionRegenRateChange;
	};
}