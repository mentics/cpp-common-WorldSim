#pragma once
#include "Agent.h"
#include "AgentControl.h"
#include "Scheduler.h"

template <typename Model , typename TimeType>
class AIController
{
public:
	AIController();
	virtual void run() = 0;

private:
	
	//SchedulerPtr<TimeType,Model> SchedPtr;
	//AgentP AgntPtr;
	
};

