#include "stdafx.h"
#include "Scheduler.cpp"
#include "WorldModel.h"

namespace MenticsGame {

template<> class SchedulerModel<WorldModel, TimePoint>;
template<> class Scheduler<WorldModel, TimePoint>;

}