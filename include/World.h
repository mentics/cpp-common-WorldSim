#pragma once

#include "MenticsCommon.h"
#include "Agent.h"
#include "Scheduler.h"
#include "WorldModel.h"
#include "gsl\gsl"
#include "Events.h"


//using SchedPtr = Scheduler<RealTime>*;
//using SchedPtr = nn::nn<Scheduler<RealTime>*>;
namespace MenticsGame {
	class AgentControl;
	using AgentControlUniquePtr = nn::nn<std::unique_ptr<AgentControl> >;

	struct RealTimeProvider : public SchedulerTimeProvider<RealTime> {
		RealTime max = 2000000000000;
		RealTime lastChangeClock = 0;
		double timeScale = 0; // Always start paused

		RealTimeProvider() {
			lastChangeClock = currentTimeNanos();
		}

		void setTimeScale(RealTime newTimeScale) {
			lastChangeClock = currentTimeNanos();
			timeScale = newTimeScale;
		}

		RealTime now();

		inline chrono::nanoseconds realTimeUntil(RealTime toGameTime) {
			if (timeScale == 0) {
				return chrono::nanoseconds((RealTime)FOREVER);
			}
			RealTime toWait = toGameTime - now();
			double v = (double)toWait / timeScale;
			if (v > FOREVER || v < 0) {
				return chrono::nanoseconds((RealTime)FOREVER);
			} else {
				return chrono::nanoseconds((RealTime)v);
			}
		}
	};
	PTRS(RealTimeProvider)

		

		class World {
		public:
			World(RealTime userInputDelay) : userInputDelay(userInputDelay), timeProv(), schedModel("SchedulerModel"), sched("Scheduler", nn::nn_addr(schedModel),nn::nn_addr(timeProv),nn::nn_addr(model))
			{
			}


			

			void setTimeScale(double newTimeScale);
			AgentControl createPlayerInput();

			RealTime userInputTimeToRun();

			AgentIndex allAgentsData(gsl::span<AgentPosVelAcc> buffer);

			std::pair<AgentControlUniquePtr, bool> getAgentControl(AgentId id);

			RealTime getGameTime() { return timeProv.now(); }
			
			void createQuip(RealTime at, TrajectoryUniquePtr&& traj);

		private:
			ONLY_MOVE(World);

			friend  WorldModel* getp(World *);
			friend Scheduler<WorldModel, RealTime>* getpSched(World *);

			RealTime userInputDelay;
			RealTimeProvider timeProv;
			SchedulerModel<WorldModel, RealTime> schedModel;
			Scheduler<WorldModel, RealTime> sched;
			WorldModel model;
	};





	

}