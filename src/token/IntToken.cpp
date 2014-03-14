#include "token/IntToken.h"

boost::shared_ptr<Token> IntToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;
  int value = 0;

  int state = 0;
  while(true) {
    char next = is.get();

    switch(state) {
      case 0:
        if(std::isdigit(next)) {
          value = next - '0';
          text += next;
          state = 1;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(std::isdigit(next)) {
          value = (value * 10) + next - '0';
          text += next;
          state = 1;
        } else {
          is.putback(next);
          return boost::shared_ptr<Token>(new IntToken(text, value));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

