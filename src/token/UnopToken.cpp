#include "token/UnopToken.h"

boost::shared_ptr<Token> UnopToken::parse(std::istream &is) {
  std::string text;

  int state = 0;
  while(true) {
    char next = is.get();
    text += next;

    switch(state) {
      case 0:
        if(next == 'n') {
          state = 1;
        } else if(next == 's') {
          state = 4;
        } else if(next == 'c') {
          state = 7;
        } else if(next == 't') {
          state = 10;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if(next == 'o') {
          state = 2;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 2:
        if(next == 't') {
          return boost::shared_ptr<Token>(new UnopToken(text, UnopToken::Not));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 3:
        break;
      case 4:
        if(next == 'i') {
          state = 5;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 5:
        if(next == 'n') {
          return boost::shared_ptr<Token>(new UnopToken(text, UnopToken::Sin));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 6:
        break;
      case 7:
        if(next == 'o') {
          state = 8;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 8:
        if(next == 's') {
          return boost::shared_ptr<Token>(new UnopToken(text, UnopToken::Cos));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 9:
        break;
      case 10:
        if(next == 'a') {
          state = 11;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 11:
        if(next == 'n') {
          return boost::shared_ptr<Token>(new UnopToken(text, UnopToken::Tan));
        } else {
          state = REJECT_STATE;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

