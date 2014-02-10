#include "token/NameToken.h"

boost::shared_ptr<Token> NameToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;

  int state = 0;
  while(true) {
    char next = is.get();

    switch(state) {
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
          is.putback(next);

          boost::shared_ptr<Token> existing = (*symbols)[text];
          if(!existing) {
            (*symbols)[text] = boost::shared_ptr<Token>(new NameToken(text));
          }

          return (*symbols)[text];
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

