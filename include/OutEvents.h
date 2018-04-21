#pragma once
#include "EventBases.h"
#include "WorldModel.h"

namespace MenticsGame {

template<typename TimeType>
struct QuipCreated : public OutEvent<TimeType> {
	QuipWP quip;
	QuipCreated(const TimeType occursAt, const QuipWP q) : OutEvent(occursAt, EventQuipCreated), quip(q){}
};

}