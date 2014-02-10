#ifndef _PAREN_TOKEN_H_
#define _PAREN_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class ParenToken : public Token {
public:
  enum Types { Left, Right };
  ParenToken(std::string text, Types type) : Token(text), type(type) {}

  std::string getTagName() { return "PAREN"; }
  Types getType() { return type; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);

private:
  Types type;
};

#endif

