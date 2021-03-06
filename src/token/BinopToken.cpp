#include "token/BinopToken.h"

boost::shared_ptr<Token> BinopToken::parse(std::istream &is, SymbolTablePtr symbols) {
  std::string text;

  int state = 0;
  while(true) {
    char next = is.get();
    text += next;

    switch(state) {
      case 0:
        if(next == '+') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Plus));
        } else if(next == '-') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Minus));
        } else if(next == '*') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Times));
        } else if(next == '/') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Divide));
        } else if(next == '%') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Modulus));
        } else if(next == '^') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Power));
        } else if(next == '=') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Equal));
        } else if(next == '!') {
          state = 11;
        } else if(next == '<') {
          state = 12;
        } else if(next == '>') {
          state = 13;
        } else if(next == 'o') {
          state = 7;
        } else if(next == 'a') {
          state = 9;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 7:
        if(next == 'r') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Or));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 9:
        if(next == 'n') {
          state = 10;
        } else {
          state = REJECT_STATE;
        }
        break;
      case 10:
        if(next == 'd') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::And));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 11:
        if(next == '=') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Neq));
        } else {
          state = REJECT_STATE;
        }
        break;
      case 12:
        if(next == '=') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Leq));
        } else {
          text.pop_back();
          is.putback(next);
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Less));
        }
        break;
      case 13:
        if(next == '=') {
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Geq));
        } else {
          text.pop_back();
          is.putback(next);
          return boost::shared_ptr<Token>(new BinopToken(text, BinopToken::Greater));
        }
        break;
      case REJECT_STATE:
        return NULL;
    }
  }
}

