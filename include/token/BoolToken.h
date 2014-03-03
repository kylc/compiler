#ifndef _BOOL_TOKEN_H_
#define _BOOL_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class BoolToken : public Token {
public:
  enum Types { True, False };
  BoolToken(std::string text, Types value) : Token(text), value(value)  {}

  std::string getTagName() { return "BOOL"; }
  unsigned int getType() { return -1; }
  Types getValue() { return value; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);

private:
  Types value;
};

#endif

