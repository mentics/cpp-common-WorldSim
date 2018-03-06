#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {
	template <typename TimeType>
	void WorldModel::createQuip(TimeType at)
	{
		Quip<RealTime> q;
		agents.quips.add(q,at);
	} 

	void WorldModel::reset(RealTime resetToTime) {
		agents.reset(resetToTime);
	}

}