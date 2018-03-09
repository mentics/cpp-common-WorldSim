#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {

void WorldModel::createQuip(RealTime at)
{
	Quip<RealTime> q;
	agents.quips.add(q,at);
}

}