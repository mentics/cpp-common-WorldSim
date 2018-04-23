#include "stdafx-worldsim.h"
#include "WorldModel.h"

namespace MenticsGame {

template<typename TimeType = TimePoint>
class Quip2 {
public:
    Quip2(Quip2<TimeType>&&) = default;
    Quip2(
        //const AgentId id, TrajectoryUniquePtr&& trajectory,
        float maxEnergy
        //, float energyRegenRate,
        //float maxAttention, float attentionRegenRate,
        //TeamId team = 2)
    )
        :
        //// Agent(id, std::move(trajectory), team),
        maxEnergy(maxEnergy)
        //, energyRegenRate(energyRegenRate), maxAttention(maxAttention),
        //attentionRegenRate(attentionRegenRate), energy(maxEnergy), attention(maxAttention)
    {

    }

private:
    ONLY_MOVE(Quip2);

    SignalValue<float, TimeType> maxEnergy;         // The current maximum energy this Quip can have.
    //SignalValue<float, TimeType> energyRegenRate;     // The current rate at which this Quip regenerates energy.
    //SignalValue<float, TimeType> maxAttention;            // The current maximum attention this Quip can have.
    //SignalValue<float, TimeType> attentionRegenRate;  // The current rate at which this Quip regenerates attention.

    //SignalValue<float, TimeType> energy;
    //SignalValue<float, TimeType> attention;
};

template <typename X>
struct Top {
    Top(X x) : x(x) {}
    X x;
};

template <typename T>
class A : Top<T> {
    A(const A<T>&) = delete;
    A& operator=(const A<T>&) = delete;

    T value;
public:
    A(A<T>&&) = default;
    A(T v) : Top(v), value(v) {}
};

template <typename T, typename TimeType = int>
struct B {
    TimeType created;
    TimeType deleted = 1;
    T value;
    B(TimeType created, TimeType deleted, T&& value) : created(created), deleted(deleted), value(std::move(value)) {}
};

int main() {
    //B<A<TimePoint>, TimePoint> b(1, 1, A<TimePoint>(1));
    B<Quip2<TimePoint>, TimePoint> b(1, 1,
        Quip2<TimePoint>(0));
    //Quip2<TimePoint>(0, makeTrajZero(), 0, 0, 0, 0));
    std::cout << "Hello World";

    return 0;
}

}
