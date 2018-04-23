#pragma once
#include "MenticsCommon.h"
#include "MenticsMath.h"
#include "Trajectory.h"
#include "Signal.h"
#include "SignalStack.h"
#include "EventBases.h"

namespace MenticsGame {

typedef uint16_t TeamId;
typedef EntityId AgentId;
typedef uint32_t AgentIndex;

struct AgentPosVelAcc {
    AgentPosVelAcc() {}
    AgentPosVelAcc(AgentId agentId, PosVelAcc pva) : agentId(agentId), pva(pva) {}
    AgentId agentId;
    PosVelAcc pva;
};


// Forward declaration of Action because Agent needs it
template<typename TimeType, typename Model> class Action;
PTRS2(Action, TimeType, Model)
#define ActionP ActionPtr<TimeType,Model>
#define ActionUP ActionUniquePtr<TimeType,Model>


////
// An Agent that can move around and do things on its own in the world.
template<typename TimeType, typename Model>
class Agent {
public:
    const AgentId id;
    const TimeType createTime;
    SignalValue<uint64_t, TimeType> thoughtPeriod;
    SignalUnique<Trajectory, TimeType> trajectory;

    // Represents which team the agent is on. Used to identify friendlies and enemies. 
    // Default value is 2 for enemy team.Value is 1 for single player's team.
    SignalValue<TeamId, TimeType> team;
    SignalValue<TimeType, TimeType> reactionTime;
    SignalValue<TimeType, TimeType> perceptionDelay;

    SignalStack<ActionUP> actions;

    Agent(Agent<TimeType, Model>&&) = default;

    Agent(const AgentId id, const TimeType createTime, TrajectoryUniquePtr&& trajectory, TeamId team = 2)
        : id(id), createTime(createTime), team(team), actions(),
        trajectory(std::move(trajectory)), thoughtPeriod(0), reactionTime(0), perceptionDelay(0) {
        // TODO: actions.push(uniquePtr<NoAction<TimeType>>(createTime);
    }

    void setAction(TimeType at, ActionUP action, SchedulatorP sched) {
        // TODO
        //while (actions.size() > 1) {
        //  actions.pop(at)->cancel(at, notNull(this), sched);
        //}
        //actions.push(at, std::move(action));
        //action->apply(at, notNull(this), sched);
    }

    void interruptAction(TimeType at, ActionUP action, SchedulatorP sched) {
        actions.peek()->pause(at, notNull(this), sched);
        actions.push(std::move(action));
        action->apply(at, notNull(this), sched);
    }

    ActionP currentAction() {
        return actions.peek();
    }

    void reset(TimeType resetTime) {
        thoughtPeriod.reset(resetTime);
        trajectory.reset(resetTime);
        team.reset(resetTime);
        reactionTime.reset(resetTime);
        perceptionDelay.reset(resetTime);
    }
};
PTRS2(Agent, TimeType, Model)
#define AgentP AgentPtr<TimeType,Model>
#define AgentUP AgentUniquePtr<TimeType,Model>

template<typename TimeType, typename Model>
class FullAgent : public Agent<TimeType, Model> {
public:
    FullAgent(const AgentId id, const TimeType createdTime, TrajectoryUniquePtr&& trajectory)
        : Agent(id, createdTime, std::move(trajectory)) {}
};

PTRS2(Boss, TimeType, Model)
#define BossP BossPtr<TimeType,Model>
#define BossUP BossUniquePtr<TimeType,Model>
template<typename TimeType, typename Model>
class Boss : public FullAgent<TimeType, Model> {
public:
    Boss(const AgentId id, const TimeType createdTime, TrajectoryUniquePtr&& trajectory) : FullAgent(id, createdTime, std::move(trajectory)) {}

    static BossUP createDefault(const AgentId id) {
        return uniquePtr<Boss<TimeType, Model>>(id, makeTrajZero());
    }
};

template<typename TimeType, typename Model>
class Minion : public FullAgent<TimeType, Model> {};
PTRS2(Minion, TimeType, Model)
#define MinionP MinionPtr<TimeType,Model>
#define MinionUP MinionUniquePtr<TimeType,Model>

template<typename TimeType, typename Model>
class Shot : public Agent<TimeType, Model> {};
PTRS2(Shot, TimeType, Model)
#define ShotP ShotPtr<TimeType,Model>
#define ShotUP ShotUniquePtr<TimeType,Model>


////
// Action represents the current interruptable behavior of the Agent. So, they can handle a temporary
// trajectory change because of user input (tempacc), or collision, or other such thing, but then return
// back to the desired action. Also, it handles the mechanism to update if a reference point trajectory
// modifies it's trajectory so this Agent needs to recalculate it's trajectory.
template<typename TimeType, typename Model>
class Action {
    virtual void apply(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;
    virtual void addListeners(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;
    virtual void removeListeners(const TimeType at, const AgentP agent, const SchedulatorP sched) const = 0;

public:
    const TimeType startTime;

    Action(const TimeType startTime) : startTime(startTime) {}

    void start(const TimeType at, const AgentP agent, const SchedulatorP sched) const {
        apply(at, agent->perceptionDelay.get(at), agent);
        addListeners(at, agent, sched);
    }

    void pause(const TimeType at, const AgentP agent, const SchedulatorP sched) const {
        removeListeners(at, agent, sched);
    }

    void resume(const TimeType at, const AgentP agent, const SchedulatorP sched) const {
        addListeners(at, agent, sched);
    }

    void cancel(const TimeType at, const AgentP agent, const SchedulatorP sched) const {
        removeListeners(at, agent, sched);
    }
};


////
// The no-op Action.
template<typename TimeType, typename Model>
struct NoAction : public Action<TimeType, Model> {
    NoAction(const TimeType startTime) : Action(startTime) {}
};

}
