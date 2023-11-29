#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine {
private:
    std::stack<StateRef> states;

public:
    void addState(StateRef newState);
    void removeState();
    StateRef &getActiveState();
};


#endif // STATEMACHINE_H
