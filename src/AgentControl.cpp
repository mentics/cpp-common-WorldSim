#include "stdafx.h"
#include "AgentControl.h"
#include "Events.h"

namespace MenticsGame {

template<typename TimeType>
void AgentControl<TimeType>::arrive(const AgentP agent, const AgentP target, double distance) {
	sched->schedule(inputDelay, uniquePtr<CmdArrive>(agent, target, distance));
}

template<typename TimeType>
void AgentControl<TimeType>::tempAcc(const vect3& dir) {
	sched->schedule(uniquePtr<CmdAcc>(now, now + inputTimeDelay, agentId, dir));
}

}
