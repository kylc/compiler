#include "token/NameToken.h"

boost::shared_ptr<Token> NameToken::parse(std::fstream &fs) {
  std::string text;

  int state = 0;
  while(true) {
    char next = fs.get();

    switch(state) {
      std::cout << "In state: " << state << " got: " << next << std::endl;
      case 0:
        if((next >= 'A' && next <= 'Z') || (next >= 'a' && next <= 'z') || next == '_') {
          state = 1;
          text += next;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 1:
        if((next >= 'A' && next <= 'Z') || (next >= 'a' && next <= 'z') || next == '_' || (next > '0' && next < '9')) {
          state = 1;
          text += next;
        } else {
          return boost::shared_ptr<Token>(new NameToken(text));
        }
    }
  }
}

