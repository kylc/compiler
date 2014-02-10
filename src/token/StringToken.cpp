#include "token/StringToken.h"

#include "util/StateMachineBuilder.h"

boost::shared_ptr<Token> StringToken::parse(std::istream &is, SymbolTablePtr symbols) {
  StateMachineBuilder b;
  // b.addState(0);
  b.addTransition('"', 0, 1);
  b.addState(1);

  for(char c = 'A'; c < 'z'; c++) {
    b.addConsumingTransition(c, 1, 1);
  }

  b.addConsumingTransition(' ', 1, 1);
  b.addTransition('"', 1, 2);
  b.addEndState(2);

  StateMachine m = b.build();
  if(m.consumeFromStream(is) == StateMachine::Accept) {
    return boost::shared_ptr<Token>(new StringToken(m.getConsumed()));
  } else {
    return NULL;
  }

  /*
  int state = 0;
  while(true) {
    char next = is.get();

    switch(state) {
      case 0:
        if(next == '"') {
          state = 1;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(next == '"') {
          return boost::shared_ptr<Token>(new StringToken(value));
        } else if(std::isalnum(next) || std::isspace(next)) {
          value += next;
        } else {
          state = REJECT_STATE;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
  */
}

