#include "stdafx.h"
#include "Quip.h"
#include "SignalFunctions.h"


Quip::Quip(const AgentId id, nn::nn_shared_ptr<Trajectory> trajectory, nn::nn_shared_ptr<Trajectory> visibleTrajectory, 
	float maxEnergy, float energyRegenRate, float maxAttention, float attentionRegenRate, uint16_t team)
	: Agent(id, trajectory, visibleTrajectory, team)
	, maxEnergy(maxEnergy), energyRegenRate(energyRegenRate), maxAttention(maxAttention), attentionRegenRate(attentionRegenRate)
, energy(SignalFunctions::ConstantFunction<double>(maxEnergy)), attention(SignalFunctions::ConstantFunction<double>(maxAttention))
{}

using namespace std::placeholders;

std::function<QuipChange(float)> QuipHelper::createMaxEnergyChange = std::bind(QuipHelper::createQuipChange, _1, boost::none, boost::none, boost::none);
std::function<QuipChange(float)> QuipHelper::createEnergyRegenRateChange = std::bind(QuipHelper::createQuipChange, boost::none, _1, boost::none, boost::none);
std::function<QuipChange(float)> QuipHelper::createMaxAttentionChange = std::bind(QuipHelper::createQuipChange, boost::none, boost::none, _1, boost::none);
std::function<QuipChange(float)> QuipHelper::createAttentionRegenRateChange = std::bind(QuipHelper::createQuipChange, boost::none, boost::none, boost::none, _1);

QuipChange QuipHelper::createQuipChange(optf p1, optf p2, optf p3, optf p4) {
	return QuipChange([=](Quip &quip) {
		if (p1) { quip.maxEnergy = p1.get();			}
		if (p2) { quip.energyRegenRate = p2.get();		}
		if (p3) { quip.maxAttention = p3.get();			}
		if (p4) { quip.attentionRegenRate = p4.get();	}
	}, std::chrono::system_clock::now().time_since_epoch().count());
}
