#include "stdafx.h"
#include "WorldModel.h"
#include "Trajectory.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at, TrajectoryUniquePtr&& traj)
{
	agents.quips.add(Quip<RealTime>(0, std::move(traj), 0, 0, 0, 0),at);
}

}