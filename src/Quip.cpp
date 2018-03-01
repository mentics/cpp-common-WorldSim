#include "stdafx.h"
#include "Quip.h"
#include <chrono>

namespace MenticsGame {

	

	using namespace std::placeholders;

	std::function<QuipChange(float)> QuipHelper::createMaxEnergyChange = std::bind(QuipHelper::createQuipChange, _1, NULL, NULL, NULL);
	std::function<QuipChange(float)> QuipHelper::createEnergyRegenRateChange = std::bind(QuipHelper::createQuipChange, NULL, _1, NULL, NULL);
	std::function<QuipChange(float)> QuipHelper::createMaxAttentionChange = std::bind(QuipHelper::createQuipChange, NULL, NULL, _1, NULL);
	std::function<QuipChange(float)> QuipHelper::createAttentionRegenRateChange = std::bind(QuipHelper::createQuipChange, NULL, NULL, NULL, _1);
	
	QuipChange QuipHelper::createQuipChange(float p1, float p2, float p3, float p4) {
	//	return QuipChange([=](Quip<> &quip) {
	//		quip.maxEnergy = p1;
	//		quip.energyRegenRate = p2;
	//		quip.maxAttention = p3;
	//		quip.attentionRegenRate = p4;
	//	}, std::chrono::system_clock::now().time_since_epoch().count());
	}
}