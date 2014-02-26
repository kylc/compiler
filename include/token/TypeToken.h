#ifndef _TYPR_TOKEN_H_
#define _TYPR_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class TypeToken : public Token {
public:
  enum Types { Bool, Int, String, Float };
  TypeToken(std::string text, Types value) : Token(text), value(value)  {}

  std::string getTagName() { return "TYPE"; }
  unsigned int getType() { return -1; }
  Types getValue() { return value; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);

private:
  Types value;
};

#endif

