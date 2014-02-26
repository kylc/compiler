#ifndef _ASSIGN_TOKEN_H_
#define _ASSIGN_TOKEN_H_

#include <istream>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class AssignToken : public Token {
public:
  AssignToken() : Token(":=") {}

  std::string getTagName() { return "ASSIGN"; }
  unsigned int getType() { return -1; }

  static boost::shared_ptr<Token> parse(std::istream &is, SymbolTablePtr symbols);
};

#endif

