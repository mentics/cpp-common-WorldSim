#pragma once

#include "MenticsMath.h"
#include "Scheduler.h"

namespace sched = mentics::scheduler;

template <typename TimeType>
class EventAcc : public sched::Event<TimeType> {
public:
	EventAcc(TimeType timeToRun, vect3 dir) : Event(timeToRun), dir(dir) {
	};

	void run(sched::Schedulator<TimeType>* sched) {

	}

private:
	vect3 dir;
};