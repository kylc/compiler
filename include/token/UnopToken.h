#ifndef _UNOP_TOKEN_H_
#define _UNOP_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class UnopToken : public Token {
public:
  enum Types { Not, Sin, Cos, Tan };
  UnopToken(std::string text, Types type) : Token(text), type(type) {}

  std::string getTagName() { return "UNOP"; }
  Types getType() { return type; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);

private:
  Types type;
};

#endif

