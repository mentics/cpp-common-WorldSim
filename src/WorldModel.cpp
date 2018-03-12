#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at)            
{
	agents.quips.add(Quip<RealTime>(0, makeTrajZero(), 0, 0, 0, 0),at);
}

}