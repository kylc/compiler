#include "token/StringToken.h"

boost::shared_ptr<Token> StringToken::parse(std::fstream &fs) {
  std::string value;

  int state = 0;
  while(true) {
    char next = fs.get();

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
}

