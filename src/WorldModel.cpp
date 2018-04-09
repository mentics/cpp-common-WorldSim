#include "stdafx.h"
#include "WorldModel.h"
#include "Trajectory.h"

namespace MenticsGame {

QuipPtr WorldModel::createQuip(RealTime at, TrajectoryUniquePtr&& traj, std::string name)
{
	mlog->info("Creating quip");
	Quip<RealTime> q(0, std::move(traj), 0, 0, 0, 0, name);
	agents.quips.add(Quip<RealTime>(0, std::move(traj), 0, 0, 0, 0, name),at);

	return nn::nn_addr(q);   
}

}