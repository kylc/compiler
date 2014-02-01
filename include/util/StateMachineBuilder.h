#ifndef _STATE_MACHINE_BUILDER_H_
#define _STATE_MACHINE_BUILDER_H_

#include "State.h"
#include "Transition.h"
#include "StateMachine.h"

class StateMachineBuilder {
public:
  void addStartState(int id);
  void addState(int id);
  void addEndState(int id);
  void addTransition(char accept, int from, int to);
  void addConsumingTransition(char accept, int from, int to);

  StateMachine build();
private:
  std::vector<State> states;
  std::vector<Transition> transitions;
};

#endif
