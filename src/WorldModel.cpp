#include "stdafx.h"
#include "WorldModel.h"
#include "Trajectory.h"

namespace MenticsGame {

template<typename TimeType>
QuipP WorldModel<TimeType>::createQuip(const TimeType at, TrajectoryUniquePtr&& traj, std::string name) {
	mlog->info("Creating quip"); 
	return agents.quips.add(Quip<TimeType>(0, std::move(traj), 0, 0, 0, 0, name), at);
}

}