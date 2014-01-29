#include "token/IntToken.h"

boost::shared_ptr<Token> IntToken::parse(std::fstream &fs) {
  std::string value;

  int state = 0;
  while(true) {
    char next = fs.get();

    switch(state) {
      case 0:
        if(next == '+' || next == '-' || std::isdigit(next)) {
          state = 1;
          value += next;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(std::isdigit(next)) {
          state = 1;
          value += next;
        } else {
          fs.putback(next);
          return boost::shared_ptr<Token>(new IntToken(value));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

