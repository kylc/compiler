#include "util/StateMachine.h"

StateMachine::MachineState StateMachine::accept(char input) {
  for(size_t i = 0; i < transitions.size(); i++) {
    Transition t = transitions[i];
    if(t.getFromState() == getCurrent().getId()) {
      if(input == t.getAccept()) {
        // TODO: Don't subtract 1, store start in list
        setCurrent(states[t.getToState() - 1]);

        if(t.isConsuming()) {
          consumed += input;
        }

        if(getCurrent().isEndState()) {
          return StateMachine::Accept;
        } else {
          return StateMachine::Continue;
        }
      }
    }
  }

  return StateMachine::Reject;
}

StateMachine::MachineState StateMachine::consumeFromStream(std::istream &is) {
  while(!getCurrent().isEndState()) {
    char c = is.get();

    StateMachine::MachineState ret = accept(c);
    if(ret != StateMachine::Continue) {
      return ret;
    }
  }

  std::cerr << "Never reached end state." << std::endl;
  exit(0);
}
