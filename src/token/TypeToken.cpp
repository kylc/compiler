#include "token/TypeToken.h"

boost::shared_ptr<Token> TypeToken::parse(std::fstream &fs) {
  std::string text;

  int state = 0;
  while(true) {
    char next = fs.get();
    text += next;

    switch(state) {
      case 0:
        if(next == 'b') {
          state = 1;
        } else if(next == 'i') {
          state = 5;
        } else if(next == 's') {
          state = 8;
        } else if(next == 'f') {
          state = 14;
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
        if(next == 'o') {
          state = 3;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 3:
        if(next == 'l') {
          return boost::shared_ptr<Token>(new TypeToken(text, TypeToken::Bool));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 4:
        break;
      case 5:
        if(next == 'n') {
          state = 6;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 6:
        if(next == 't') {
          return boost::shared_ptr<Token>(new TypeToken(text, TypeToken::Int));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 7:
        break;
      case 8:
        if(next == 't') {
          state = 9;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 9:
        if(next == 'r') {
          state = 10;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 10:
        if(next == 'i') {
          state = 11;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 11:
        if(next == 'n') {
          state = 12;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 12:
        if(next == 'g') {
          return boost::shared_ptr<Token>(new TypeToken(text, TypeToken::String));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 13:
        break;
      case 14:
        if(next == 'l') {
          state = 15;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 15:
        if(next == 'o') {
          state = 16;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 16:
        if(next == 'a') {
          state = 17;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 17:
        if(next == 't') {
          return boost::shared_ptr<Token>(new TypeToken(text, TypeToken::Float));
        } else {
          state = REJECT_STATE;
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

