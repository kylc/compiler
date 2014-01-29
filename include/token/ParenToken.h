#ifndef _PAREN_TOKEN_H_
#define _PAREN_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class ParenToken : public Token {
public:
  enum Types { Left, Right };
  ParenToken(std::string text, Types type) : Token(text), type(type) {}

  std::string getTagName() { return "PAREN"; }
  Types getType() { return type; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);

private:
  Types type;
};

#endif

