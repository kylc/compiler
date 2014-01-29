#include "token/ParenToken.h"

boost::shared_ptr<Token> ParenToken::parse(std::fstream &fs) {
  char next = fs.get();
  std::string text(1, next);

  boost::shared_ptr<Token> token = NULL;
  if(next == '[') {
    token = boost::shared_ptr<Token>(new ParenToken(text, ParenToken::Left));
  } else if(next == ']') {
    token = boost::shared_ptr<Token>(new ParenToken(text, ParenToken::Right));
  }

  return token;
}

