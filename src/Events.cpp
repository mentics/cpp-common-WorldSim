#include "stdafx-worldsim.h"
#include "Events.h"
#include "OutEvents.h"
#include "TrajectoryCalculator.h"

namespace MenticsGame {

template<typename TimeType>
void EventCreateQuip<TimeType>::run(SchedulatorWP sched, WorldModelP model) {
    sched->addOutEvent(nn::nn_make_unique<QuipCreated<TimeType>>(timeToRun,
        model->createQuip(created, std::move(traj), name)));
}

template<typename TimeType>
void CmdArrive<TimeType>::run(SchedulatorWP sched, WorldModelP model) {
    // TODO: call agent set action and inside that method, set action and trajectory.
    // TODO: Hopefully we'll get notified when target is destroyed so we can change action before we try to go back
    agent->trajectory.add(TRAJ_CALC.arrive(timeToRun, nn::nn_addr(*agent->trajectory.get(timeToRun)), nn::nn_addr(*target->trajectory.get(timeToRun)), dist), timeToRun);
}

template<typename TimeType>
void CmdAcc<TimeType>::run(SchedulatorWP sched, WorldModelP model) {
    // TODO
    const TimeType LONG_ENOUGH = 50000000; // TODO: how long?
    //Agent* a = model->agent(agentId);
    //Trajectory& curTraj = *a->trajectory;
    //std::shared_ptr<Trajectory> visible;
    //if (a->trajectory->startTime < (timeToRun - LONG_ENOUGH)) {
    //  visible = a->trajectory;
    //}
    //vect3 pos;
    //vect3 vel;

    //curTraj.posVel(timeToRun, pos, vel);
    //nn::nn_shared_ptr<Trajectory> newTraj = nn::nn_make_shared<BasicTrajectory>(timeToRun, FOREVER, pos, vel, dir);
//      model->change(uniquePtrC<Change2, TrajectoryChange>(timeToRun, agentId, newTraj, visible));
}

//void TrajectoryChange::apply(WorldModelPtr model) {
//  Agent* a = model->agent(agentId);
//  if (a == nullptr) {
//      // TODO: ERROR? or could it have been destroyed?
//  }
//  else {
//      a->trajectory = std::move(newTraj);
//      if (newVisibleTraj != nullptr) {
//          a->visibleTrajectory = NN_CHECK_ASSERT(newVisibleTraj);
//      }
//  }
//}
}
