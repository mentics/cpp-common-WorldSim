#include "stdafx.h"
#include "WorldModel.h"

namespace MenticsGame {
	void WorldModel::reset(RealTime resetToTime) {
		reset.reset(resetToTime);
	}
}