#include "stdafx.h"
#include "CppUnitTest.h"
#include "MenticsCommonTest.h"
#include "Quip.h"
#include "Actions.h"
#include "WorldModel.h"
//#include "../Actions.cpp" // remove this when 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MenticsGame {

TEST_CLASS(WorldSimTest) {
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		setupLog();
	}

	TEST_METHOD(TestActionArrive) {
		QuipUniquePtr<TimePoint,WorldModel<TimePoint>> quip = Quip<TimePoint,WorldModel<TimePoint>>::createDefault(0);
		BossUniquePtr<TimePoint,WorldModel<TimePoint>> boss = Boss<TimePoint,WorldModel<TimePoint>>::createDefault(1);
		ActionArrive<TimePoint> action(0, notNull(boss.get()), 2.0);
		//action.apply(quip);
	}
};

}
