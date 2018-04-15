#pragma once

#include "EventBases.h"
#include "Quip.h"

namespace MenticsGame {

template<typename TimeType>
struct QuipCreated : public OutEvent<TimeType> {
	QuipP quip;
	QuipCreated(const TimeType occursAt, const QuipP q) : OutEvent(occursAt), quip(q) {}
};

}