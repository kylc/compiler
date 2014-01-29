#ifndef _PAREN_TOKEN_H_
#define _PAREN_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class ParenToken : public Token {
public:
  ParenToken(std::string value) : Token(value) {}

  std::string getTagName() { return "PAREN"; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);
};

#endif

