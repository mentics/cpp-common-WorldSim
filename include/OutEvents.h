#pragma once

#include "EventBases.h"
#include "Quip.h"

namespace MenticsGame {

template<typename TimeType>
struct QuipCreated : public OutEvent<TimeType> {
	const std::string name;
	QuipP quip;
	QuipCreated(const TimeType occursAt, const std::string name, const QuipP q) : OutEvent(occursAt), name(name), quip(q) {}
};

}