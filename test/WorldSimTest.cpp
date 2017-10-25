#include "stdafx.h"
#include "CppUnitTest.h"

#include "World.h"
#include "UserInput.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WorldSimTest {
	TEST_CLASS(WorldSimTest) {
	public:
		TEST_METHOD(TestWorld) {
			World<RealTime>* world = startWorld();
			AgentId playerId = createPlayerInput(world);
			tempAcc(world, playerId, vect3(1, 1, 1));
		}
	};
}