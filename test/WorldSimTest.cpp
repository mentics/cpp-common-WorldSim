#include "stdafx.h"
#include "CppUnitTest.h"

#include "World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WorldSimTest {
	TEST_CLASS(WorldSimTest) {
	public:
		TEST_METHOD(TestWorld) {
			World world;
			world.start();
		}
	};
}