#include "stdafx.h"
#include "Quip.h"
#include "SignalFunctions.h"

namespace MenticsGame {
	Quip::Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory,
		float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, uint16_t team)
		: Agent(id, trajectory, visibleTrajectory, team)
		, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
		, energy(SignalFunctions::ConstantFunction<double>(maxEnergy)), attention(SignalFunctions::ConstantFunction<double>(maxAttention))
	{}

	using namespace std::placeholders;

	//std::function<QuipChange(float)> QuipHelper::createMaxEnergyChange = std::bind(QuipHelper::createQuipChange, _1, NULL, NULL, NULL);
	//std::function<QuipChange(float)> QuipHelper::createEnergyRegenRateChange = std::bind(QuipHelper::createQuipChange, NULL, _1, NULL, NULL);
	//std::function<QuipChange(float)> QuipHelper::createMaxAttentionChange = std::bind(QuipHelper::createQuipChange, NULL, NULL, _1, NULL);
	//std::function<QuipChange(float)> QuipHelper::createAttentionRegenRateChange = std::bind(QuipHelper::createQuipChange, NULL, NULL, NULL, _1);
	//
	//QuipChange QuipHelper::createQuipChange(float p1, float p2, float p3, float p4) {
	//	return QuipChange([=](Quip &quip) {
	//		quip.maxEnergy = p1;
	//		quip.energyRegenRate = p2;
	//		quip.maxAttention = p3;
	//		quip.attentionRegenRate = p4;
	//	}, std::chrono::system_clock::now().time_since_epoch().count());
	//}
}