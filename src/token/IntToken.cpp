#include "token/IntToken.h"

boost::shared_ptr<Token> IntToken::parse(std::fstream &fs) {
  std::string text;
  bool positive = true;
  int value = 0;

  int state = 0;
  while(true) {
    char next = fs.get();

    switch(state) {
      case 0:
        if(next == '+') {
          positive = true;
          text += next;
        } else if(next == '-') {
          positive = false;
          text += next;
        } else if(std::isdigit(next)) {
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
          fs.putback(next);
          value = positive ? value : -value;
          return boost::shared_ptr<Token>(new IntToken(text, value));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

