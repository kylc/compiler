#ifndef _STRING_TOKEN_H_
#define _STRING_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class StringToken : public Token {
public:
  StringToken(std::string value) : Token(value) {}

  std::string getTagName() { return "STRING"; }
  std::string getValue() { return value; }

  static boost::shared_ptr<Token> parse(std::istream &is);

private:
  std::string value;
};

#endif

