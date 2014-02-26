#include "token/AssignToken.h"

boost::shared_ptr<Token> AssignToken::parse(std::istream &is, SymbolTablePtr symbols) {
  int state = 0;
  while(true) {
    char next = is.get();

    switch(state) {
      case 0:
        if(next == ':') {
          state = 1;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(next == '=') {
          state = 1;
          return boost::shared_ptr<Token>(new AssignToken());
        } else {
          state = REJECT_STATE;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

