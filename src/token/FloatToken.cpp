#include "token/FloatToken.h"

boost::shared_ptr<Token> FloatToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;
  bool positive = true;
  float value = 0;
  int base = 10;

  int state = 0;
  while(true) {
    char next = is.get();

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
        } else if(next == '.') {
          text += next;
          state = 2;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 2:
        if(std::isdigit(next)) {
          text += next;
          value += ((float) (next - '0')) / base;
          base *= 10;
        } else {
          is.putback(next);
          value = positive ? value : -value;
          return boost::shared_ptr<Token>(new FloatToken(text, value));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

