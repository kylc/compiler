#ifndef _BINOP_TOKEN_H_
#define _BINOP_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class BinopToken : public Token {
public:
  enum Types { Plus, Minus, Times, Divide, Modulus, Power, Or, And };
  BinopToken(std::string text, Types type) : Token(text), type(type) {}

  std::string getTagName() { return "UNOP"; }
  Types getType() { return type; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);

private:
  Types type;
};

#endif
