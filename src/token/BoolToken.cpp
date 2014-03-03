#include "token/BoolToken.h"

boost::shared_ptr<Token> BoolToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;

  int state = 0;
  while(true) {
    char next = is.get();
    text += next;

    switch(state) {
      case 0:
        if(next == 't') {
          state = 1;
        } else if(next == 'f') {
          state = 5;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(next == 'r') {
          state = 2;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 2:
        if(next == 'u') {
          state = 3;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 3:
        if(next == 'e') {
          return boost::shared_ptr<Token>(new BoolToken(text, BoolToken::True));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 4:
        break;
      case 5:
        if(next == 'a') {
          state = 6;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 6:
        if(next == 'l') {
          state = 7;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 7:
        if(next == 's') {
          state = 8;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 8:
        if(next == 'e') {
          return boost::shared_ptr<Token>(new BoolToken(text, BoolToken::False));
        } else {
          state = REJECT_STATE;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

