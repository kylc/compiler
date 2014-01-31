#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <iostream>
#include <string>
#include <vector>

class State {
public:
  State(int id, bool endState) : id(id), endState(endState) {}

  int getId() { return id; }
  bool isEndState() { return endState; }

private:
  int id;
  bool endState;
};

class Transition {
public:
  Transition(char accept, int fromState, int toState, bool consuming)
    : accept(accept), fromState(fromState), toState(toState), consuming(consuming) {}

  char getAccept() { return accept; }
  int getFromState() { return fromState; }
  int getToState() { return toState; }
  bool isConsuming() { return consuming; }

private:
  char accept;
  int fromState;
  int toState;
  bool consuming;
};

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
