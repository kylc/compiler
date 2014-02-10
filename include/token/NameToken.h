#ifndef _NAME_TOKEN_H_
#define _NAME_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class NameToken : public Token {
public:
  NameToken(std::string text) : Token(text) {}

  std::string getTagName() { return "NAME"; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);
};

#endif

