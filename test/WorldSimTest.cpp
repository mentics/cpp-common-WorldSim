#include "stdafx.h"

#include "CppUnitTest.h"
#include "MenticsCommon.h"
#include "World.h"
#include "Scheduler.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono_literals;

namespace MenticsGame {

TEST_CLASS(WorldSimTest)
{
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		setupLog();
	}

	TEST_METHOD(TestWorldSim) {
		World w(0);
	}
};

}