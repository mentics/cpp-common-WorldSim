#include "stdafx.h"
#include "CppUnitTest.h"

#include "World.h"
#include "UserInput.h"

#include "MenticsCommonTest.h"

#include "Scheduler.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono_literals;

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

		TEST_METHOD(TestSharedPtr) {
			std::shared_ptr<int> p1 = std::make_shared<int>(10);
			std::shared_ptr<int> p2 = p1;
			Assert::AreEqual(10, *p1);
			Assert::AreEqual(10, *p2);
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
			// TODO: add a "wait until processed" thing
			std::this_thread::sleep_for(100ms);

			num = world.allAgentsData(agentsData);
			Assert::AreEqual(1, (int)num);
			Assert::IsTrue(isAllPos(agentsData[0].pva.pos));
			Assert::IsTrue(isAllPos(agentsData[0].pva.vel));
			Assert::IsTrue(agentsData[0].pva.acc.isApprox(vect3(1, 1, 1), EXACT_EPS));
		}

		bool isAllPos(const vect3& v) {
			return v[0] > 0 && v[1] > 0 && v[2] > 0;
		}

		struct Ray {
			vect3 dir;
			vect3 start;
		};

		typedef vect3 vec3;

		float dot(const vec3& v1, const vec3& v2) {
			return v1.dot(v2);
		}

		vec3 normalize(const vec3& v) {
			return v.normalized();
		}


		bool intersectBlob(Ray ray, vec3& intersection, vec3& normal) {
			float mag2 = dot(intersection, intersection);
			if (mag2 < 0.000000001) {
				return false;
			}

			vec3 test = intersection;
			float t = 0;

			vec3 grad = -2.0 * test / (mag2 * mag2);
			float raygrad = dot(ray.dir, grad);

			float value = 1.0 / mag2;
			float tmax = (1.0 - value) / raygrad;
			float tmin = 0;
			int i = 0;
			for (; i<20; i++) {
				test = intersection + t * ray.dir;
				mag2 = dot(test, test);

				grad = -2.0 * test / (mag2 * mag2);
				raygrad = dot(ray.dir, grad);
				if (raygrad < 0) {
					// We jumped too far to the other side, so back up.
					tmax = t;
					t = (tmax + tmin) / 2.0;
					continue;
				}
				else if (abs(raygrad) < 0.001) {
					// hit saddle point or nearest point, so it's a miss
					return false;
				}

				value = 1.0 / mag2;
				if (abs(value - 1.0) < 0.01) {
					break;
				} else if (value > 1.0) {
					// went too far, we're inside now
					tmax = t;
					t = (tmax + tmin) / 2.0;
				} else {
					tmin = t;
				}

				t = (tmax + tmin) / 2.0;
			}
			if (i == 20) {
				return false;
			} else {
				normal = -normalize(grad);
				return true;
			}
		}

		TEST_METHOD(TestElse) {
			{
				vec3 intersection(0, 0, -2);
				vec3 normal(0, 0, 0);
				intersectBlob(Ray{vec3(0, 0, 1), vec3(0, 0, -10)}, intersection, normal);
				Assert::AreEqual(-1, normal[2], 0.01);
			}

			{
				// miss on purpose
				Ray ray{ vec3(0.1, 0.1, 0.9).normalized(), vec3(0, 0, -10) };
				vec3 intersection;
				intersection = ray.start + 9 * ray.dir;
				vec3 normal(0, 0, 0);
				Assert::IsFalse(intersectBlob(ray, intersection, normal));
			}

			{
				Ray ray{ vec3(0.01, 0.01, 0.9).normalized(), vec3(0, 0, -10) };
				vec3 intersection;
				intersection = ray.start + 9 * ray.dir;
				vec3 normal(0, 0, 0);
				Assert::IsTrue(intersectBlob(ray, intersection, normal));
				//Assert::AreEqual(-1, normal[2], 0.01);
			}
		}
	};
}