#ifndef _BINOP_TOKEN_H_
#define _BINOP_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class BinopToken : public Token {
public:
  enum Types { Plus, Minus, Times, Divide, Modulus, Power, Equal, Or, And, Neq, Less, Greater, Leq, Geq };
  BinopToken(std::string text, Types type) : Token(text), type(type) {}

  std::string getTagName() { return "BINOP"; }
  unsigned int getType() { return type; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);

private:
  Types type;
};

#endif

