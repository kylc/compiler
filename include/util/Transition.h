#ifndef _TRANSITION_H_
#define _TRANSITION_H_

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

#endif
