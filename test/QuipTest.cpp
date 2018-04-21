#include "stdafx.h"
#include "CppUnitTest.h"
#include "MenticsCommonTest.h"
#include "Quip.h"
#include "Actions.h"
#include "SchedulerModel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MenticsGame {

TEST_CLASS(MenticsGame) {
	class MockSchedulator : public Schedulator<TimePoint,WorldModel<TimePoint>> {
		void schedule(TimePoint afterDuration, EventUniquePtr<TimePoint,WorldModel<TimePoint>>&& ev) override {

		}

		void addOutEvent(OutEventUniquePtr<TimePoint>&& outEvent) override {

		}

		//virtual void listen(const UpdateKey k, std::function<void(SchedulatorP const)> handler) = 0;
		void listen(const UpdateKey k, std::function<void(SchedulatorPtr<TimePoint,WorldModel<TimePoint>> const)> handler) override {
		}
	};
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		setupLog();
	}

	TEST_METHOD(TestQuipDefaultTrajectory) {
		QuipUniquePtr<TimePoint,WorldModel<TimePoint>> quip = Quip<TimePoint, WorldModel<TimePoint>>::createDefault(0);
		PosVelAcc pva;
		quip->trajectory.get(0)->posVelAcc(0, nn::nn_addr(pva));
		Assert::AreEqual(PosVelAcc({ vect3(0,0,0), vect3(0,0,0), vect3(0,0,0) }), pva);

		quip->trajectory.get(100)->posVelAcc(0, nn::nn_addr(pva));
		Assert::AreEqual(PosVelAcc({ vect3(0,0,0), vect3(0,0,0), vect3(0,0,0) }), pva);
	}

	TEST_METHOD(TestQuipAction) {
		QuipUniquePtr<TimePoint, WorldModel<TimePoint>> quip = Quip<TimePoint, WorldModel<TimePoint>>::createDefault(0);
		BossUniquePtr<TimePoint, WorldModel<TimePoint>> target = Boss<TimePoint, WorldModel<TimePoint>>::createDefault(1);

		MockSchedulator sched;
		quip->setAction(10, uniquePtr<ActionArrive<TimePoint>>(1, toPtr(target), 2.0), nn::nn_addr(sched));
	}
};

}
