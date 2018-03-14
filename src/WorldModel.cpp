#include "stdafx.h"
#include "WorldModel.h"
#include "Trajectory.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at)            
{
	agents.quips.add(Quip<RealTime>(0, nn::nn_make_unique<BasicTrajectory>(BasicTrajectory(0,0,vect3(1,1,1),vect3(1,1,1),vect3(1,1,1))), 0, 0, 0, 0),at);   //nn::nn_make_unique<BasicTrajectory>(BasicTrajectory::randomBasicTrajectory())
}

}