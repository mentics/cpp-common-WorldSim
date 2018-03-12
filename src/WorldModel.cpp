#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at)            
{
	Quip<RealTime> q(0,makeTrajZero(), 0,0,0,0);                                   

	agents.quips.add(q,at);
}

}