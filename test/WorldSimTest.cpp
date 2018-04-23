#include "stdafx-worldsimtest.h"
#include "CppUnitTest.h"
#include "MenticsCommonTest.h"
#include "World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono_literals;

namespace MenticsGame {

TEST_CLASS(WorldSimTest) {
public:
    TEST_CLASS_INITIALIZE(BeforeClass) {
        setupLog();
    }

    TEST_METHOD(TestWorldSim) {
        World w();
    }
};

}
