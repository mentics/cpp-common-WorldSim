#include "stdafx.h"
#include "CppUnitTest.h"

#include "World.h"
#include "UserInput.h"

#include "MenticsCommonTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const double EXACT_EPS = 1E-18;

namespace WorldSimTest {

	class Something {};

	//struct TestUniquePtr {
	//	TestUniquePtr(nn::nn<std::unique_ptr<Something>> theValue) : value(std::move(theValue)) {}
	//	nn::nn<std::unique_ptr<Something>> value;
	//};

	struct TestUniquePtr {
		TestUniquePtr(nn::nn<std::unique_ptr<Something>> theValue) : value(std::move(theValue)) {}
		nn::nn<std::unique_ptr<Something>> value;
	};

	void testEmplace() {
		std::vector<TestUniquePtr> v;
		//v.emplace_back(nullptr);
		//v.emplace_back(std::move(std::make_unique<Something>()));
		v.emplace_back(nn::nn_make_unique<Something>());
		//TestUniquePtr test(nullptr);
	}

	TEST_CLASS(WorldSimTest) {
	public:
		TEST_CLASS_INITIALIZE(BeforeClass) {
			mentics::test::setupLog();
		}

		TEST_METHOD(TestEmplace) {
			testEmplace();
		}

		TEST_METHOD(TestPointerThing) {
			std::vector<vect3> v;
			v.emplace_back(vect3(1, 1, 1));
			Assert::AreEqual(1.0, v.back()[0]);
			vect3* vp = &v.back();
			Assert::AreEqual(1.0, (*vp)[0]);
			v.erase(v.begin());
			Assert::AreEqual(0, (int)v.size());
			Assert::AreEqual(1.0, (*vp)[0]); // It works because it didn't delete or clear the memory?
			v.emplace_back(vect3(2, 2, 2));
			Assert::AreEqual(2.0, (*vp)[0]); // It overwrote the previous location with the new data
		}

		TEST_METHOD(TestWorld) {
			World world(100000000);
			Agent* player = world.createPlayer();
			world.setTimeScale(1);

			AgentPosVelAcc agentsData[10];
			size_t num = world.allAgentsData(agentsData);
			Assert::AreEqual(1, (int)num);
			Assert::IsTrue(agentsData[0].pva.pos.isZero());
			Assert::IsTrue(agentsData[0].pva.vel.isZero());
			Assert::IsTrue(agentsData[0].pva.acc.isZero());

			const double dir[] = { 1,1,1 };

			num = world.allAgentsData(agentsData);
			Assert::AreEqual(1, (int)num);
			Assert::IsTrue(isAllPos(agentsData[0].pva.pos));
			Assert::IsTrue(isAllPos(agentsData[0].pva.vel));
			Assert::IsTrue(agentsData[0].pva.acc.isApprox(vect3(1, 1, 1), EXACT_EPS));
		}

		bool isAllPos(const vect3& v) {
			return v[0] > 0 && v[1] > 0 && v[2] > 0;
		}
	};
}