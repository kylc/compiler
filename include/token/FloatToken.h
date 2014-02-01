#ifndef _FLOAT_TOKEN_H_
#define _FLOAT_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class FloatToken : public Token {
public:
  FloatToken(std::string text, float value) : Token(text), value(value) {}

  std::string getTagName() { return "FLOAT"; }
  float getValue() { return value; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);

private:
  float value;
};

#endif

