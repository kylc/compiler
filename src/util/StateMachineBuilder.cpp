#include "util/StateMachineBuilder.h"

void StateMachineBuilder::addState(int id) {
  State st(id, false);
  states.push_back(st);
}

void StateMachineBuilder::addEndState(int id) {
  State st(id, true);
  states.push_back(st);
}

void StateMachineBuilder::addTransition(char accept, int from, int to) {
  Transition t(accept, from, to, false);
  transitions.push_back(t);
}

void StateMachineBuilder::addConsumingTransition(char accept, int from, int to) {
  Transition t(accept, from, to, true);
  transitions.push_back(t);
}

StateMachine StateMachineBuilder::build() {
  State start(0, false);
  return StateMachine(states, transitions, start);
}

