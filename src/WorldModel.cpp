#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at)            
{
	      
	Quip<RealTime> q(0,UnqSignal<Trajectory, RealTime> (nn::nn_unique_ptr<Trajectory>(makeTrajZero())), 0,0,0,0,0);   

	agents.quips.add(q,at);
}

}