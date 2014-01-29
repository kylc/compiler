#ifndef _STRING_TOKEN_H_
#define _STRING_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class StringToken : public Token {
public:
  StringToken(std::string value) : Token(value) {}

  std::string getTagName() { return "STRING"; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);
};

#endif

