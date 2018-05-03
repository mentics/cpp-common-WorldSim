#pragma once
#include "WorldModel.h"
#include "Agent.h"
#include "TrajectoryCalculator.h"

namespace MenticsGame {

template<typename TimeType>
class ActionArrive : public Action<TimeType,WorldModel<TimeType>> {
public:
	const AgentWP target;
	const DistType distance;

	ActionArrive(const TimeType startTime, const AgentWP target, const DistType distance)
		: Action(startTime), target(target), distance(distance) {}

private:
	//virtual void apply(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;
	//virtual void addListeners(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;
	//virtual void removeListeners(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;

	// Apply this action to the provided agent
	void apply(const TimeType applyTime, const AgentWP agent, const SchedulatorWP sched) const override {
		TimeType perceptionTime = agent->perceptionDelay.get(applyTime);
        agent->trajectory.add(TRAJ_CALC.arrive(applyTime,
            agent->trajectory.get(perceptionTime),
			target->trajectory.get(perceptionTime), distance, agent->trajectory.get(applyTime)),
			applyTime);
	}

	void addListeners(const TimeType at, const AgentWP agent, const SchedulatorWP sched) const override {
		sched->listen(UpdateKey{ target->id, deleted }, [agent](const SchedulatorWP sched) {
			// TODO: destroy this action
		});
		sched->listen(UpdateKey{ target->id, changeTraj }, [agent](const SchedulatorWP sched) {

		});
	}

	void removeListeners(const TimeType at, const AgentWP agent, const SchedulatorWP sched) const override {
		// TODO
	}
};

}