#include "token/StringToken.h"

boost::shared_ptr<Token> StringToken::parse(std::istream &is, SymbolTablePtr symbols) {
  int state = 0;
  std::string value = "";

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
        } else {
          value += next;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

