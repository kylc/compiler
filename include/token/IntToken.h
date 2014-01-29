#ifndef _INT_TOKEN_H_
#define _INT_TOKEN_H_

#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class IntToken : public Token {
public:
  IntToken(std::string value) : Token(value) {}

  std::string getTagName() { return "INT"; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);
};

#endif

