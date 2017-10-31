#include "stdafx.h"
#include "CppUnitTest.h"

#include "World.h"
#include "UserInput.h"

#include "MenticsCommonTest.h"

#include "Scheduler.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const double EXACT_EPS = 1E-18;

namespace WorldSimTest {

	//Assert::IsTrue(std::is_copy_assignable<std::unique_ptr<MyStruct>>::value);
	//Assert::IsTrue(std::is_copy_constructible<std::unique_ptr<MyStruct>>::value);
	//Assert::IsTrue(!std::is_destructible<std::unique_ptr<MyStruct>>::value);

	struct Something {
		int val = 2;
	};


	struct MyStruct {
		int val = 2;

		MyStruct(const int val) : val(val) {}
	};

	void testDeque() {
		{ // This block compiles fine.
			std::deque<std::unique_ptr<MyStruct>> q1;
			q1.emplace_back(std::make_unique<MyStruct>(10));

			std::deque<std::unique_ptr<MyStruct>> q2;
			q2.push_back(std::move(q1.front()));
			q1.pop_back();
		}

		{ // This block won't compile because of q1.top()
			std::priority_queue<std::unique_ptr<MyStruct>> q1;
			q1.emplace(std::make_unique<MyStruct>(10));
			std::deque<std::unique_ptr<MyStruct>> q2;
			// How can I "peek" at the value at q1.top() without taking ownership of the unique_ptr?
			MyStruct* nonOwnershipPtr = q1.top().get();
			Assert::AreEqual(10, nonOwnershipPtr->val);
			//q2.push_back(std::move(q1.top()));// <- compiler error
			//q1.pop();
		}

		{
			std::priority_queue<std::unique_ptr<MyStruct>, std::deque<std::unique_ptr<MyStruct>>> q1;
			q1.emplace(std::make_unique<MyStruct>(10));
			std::deque<std::unique_ptr<MyStruct>> q2;
			//q2.push_back(std::unique_ptr<MyStruct>(q1.top().get()));
			//q2.push_back(q1.top()); // <- compiler error "attempting to reference a deleted function"
			q2.push_back(std::move(const_cast<std::unique_ptr<MyStruct>&>(q1.top()))); // <- compiler error "attempting to reference a deleted function"
			q1.pop();
			Assert::AreEqual(10, q2.back()->val);
		}
	}

	//std::priority_queue<std::unique_ptr<MyStruct>, std::vector<std::unique_ptr<MyStruct>>> q1;

	//struct TestUniquePtr {
	//	TestUniquePtr(nn::nn<std::unique_ptr<Something>> theValue) : value(std::move(theValue)) {}
	//	nn::nn<std::unique_ptr<Something>> value;
	//};

	//struct TestUniquePtr {
	//	TestUniquePtr(nn::nn<std::unique_ptr<Something>> theValue) : value(std::move(theValue)) {}
	//	nn::nn<std::unique_ptr<Something>> value;
	//};

	//void testEmplace() {
	//	std::vector<TestUniquePtr> v;
	//	//v.emplace_back(nullptr); // <- compile error
	//	//v.emplace_back(std::move(std::make_unique<Something>())); // <- compile error
	//	v.emplace_back(uniquePtr<Something>());

	//	nn::nn<std::unique_ptr<Something>> ptr = nn::nn_make_unique<Something>();
	//	v.emplace_back(std::move(ptr));
	//	//Assert::AreEqual(2, ptr->val); <- NPE
	//	//TestUniquePtr test(nullptr); <- compile error
	//}

	TEST_CLASS(WorldSimTest) {
	public:
		TEST_CLASS_INITIALIZE(BeforeClass) {
			setupLog();
		}

		TEST_METHOD(TestEmplace) {
			//testEmplace();
			testDeque();
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
			UserInput player = world.createPlayerInput();
			world.setTimeScale(1);

			AgentPosVelAcc agentsData[10];
			size_t num = world.allAgentsData(agentsData);
			Assert::AreEqual(1, (int)num);
			Assert::IsTrue(agentsData[0].pva.pos.isZero());
			Assert::IsTrue(agentsData[0].pva.vel.isZero());
			Assert::IsTrue(agentsData[0].pva.acc.isZero());

			const vect3 dir(1,1,1);
			player.tempAcc(dir);

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