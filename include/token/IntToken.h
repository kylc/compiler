#ifndef _INT_TOKEN_H_
#define _INT_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class IntToken : public Token {
public:
  IntToken(std::string text, int value) : Token(text), value(value) {}

  std::string getTagName() { return "INT"; }
  int getValue() { return value; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);

private:
  int value;
};

#endif

