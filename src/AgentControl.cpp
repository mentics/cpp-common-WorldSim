#include "stdafx.h"
#include "AgentControl.h"
#include "Events.h"

namespace MenticsGame {
	void AgentControl::tempAcc(const vect3& dir) {
		RealTime now = timeProv->now();
		//sched->schedule(uniquePtr<EventAcc>(now, now + inputTimeDelay, agentId, dir)); // inputTimeDelay not a member anymore
	}

	//void AgentControl::scheduleNext(AIController<WorldModel, RealTime>* contr)
	//{
	//	
	//}

	
}