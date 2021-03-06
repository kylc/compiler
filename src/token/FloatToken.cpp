#include "token/FloatToken.h"

boost::shared_ptr<Token> FloatToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;
  float value = 0;
  int base = 10;
  int power = 0;
  bool powerPositive = true;

  int state = 0;
  while(true) {
    char next = is.get();

    switch(state) {
      case 0:
        if(std::isdigit(next)) {
          value = next - '0';
          text += next;
          state = 1;
        } else if(next == '.') {
          text += next;
          state = 2;
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
        } else if(next == 'e' || next == 'E') {
          text += next;
          state = 3;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 2:
        if(std::isdigit(next)) {
          text += next;
          value += ((float) (next - '0')) / base;
          base *= 10;
        } else if(next == 'e' || next == 'E') {
          text += next;
          state = 3;
        } else {
          is.putback(next);
          return boost::shared_ptr<Token>(new FloatToken(text, value));
        }
        break;
      case 3:
        if(next == '-') {
          text += next;
          powerPositive = false;
        } else if(std::isdigit(next)) {
          text += next;
          power = (power * 10) + next - '0';
        } else {
          is.putback(next);

          if(!powerPositive) {
            power = -power;
          }
          return boost::shared_ptr<Token>(new FloatToken(text, value * pow(10, power)));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

