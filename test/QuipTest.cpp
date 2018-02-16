#include "stdafx.h"
#include "CppUnitTest.h"
#include "MenticsCommon.h"
#include "MenticsCommonTest.h"
#include "Trajectory.h"
#include "Quip.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MenticsGame {
	TEST_CLASS(QuipTest)
	{

		const std::string name = "ResettableTest";

	public:
		TEST_CLASS_INITIALIZE(BeforeClass) {
			//setupLog();
		}

		TEST_METHOD(TestQuipCreateChange) {
			vect3 zero(0, 0, 0);
			auto t1 = nn::nn_make_shared<BasicTrajectory>(100, 100, zero, zero, zero);
			auto t2 = nn::nn_make_shared<BasicTrajectory>(100, 100, zero, zero, zero);
			Quip quip(1, t1, t2, 1, 2, 3, 4);
			{
				auto change = QuipHelper::createMaxEnergyChange(10);
				change.action(quip);
				Assert::AreEqual(10.f, quip.maxEnergy);
			}
			{
				auto change = QuipHelper::createMaxAttentionChange(10);
				change.action(quip);
				Assert::AreEqual(10.f, quip.maxAttention);
			}
			{
				auto change = QuipHelper::createEnergyRegenRateChange(10);
				change.action(quip);
				Assert::AreEqual(10.f, quip.energyRegenRate);
			}
			{
				auto change = QuipHelper::createAttentionRegenRateChange(10);
				change.action(quip);
				Assert::AreEqual(10.f, quip.attentionRegenRate);
			}
		}
	};
}