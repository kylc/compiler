#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "State.h"
#include "Transition.h"

#include <iostream>
#include <string>
#include <vector>

class StateMachine {
public:
  enum MachineState { Reject, Continue, Accept };

  StateMachine(std::vector<State> states, std::vector<Transition> transitions, State start) : states(states), transitions(transitions), current(start) {}

  State getCurrent() { return current; }
  void setCurrent(State st) { current = st; }

  std::string getConsumed() { return consumed; }

  MachineState accept(char input);

  StateMachine::MachineState consumeFromStream(std::istream &is);
private:
  std::vector<State> states;
  std::vector<Transition> transitions;

  State current;

  std::string consumed;
};

#endif
