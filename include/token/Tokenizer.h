#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <istream>
#include <unordered_map>
#include <boost/shared_ptr.hpp>

#include "Token.h"
#include "AssignToken.h"
#include "ParenToken.h"
#include "StringToken.h"
#include "FloatToken.h"
#include "IntToken.h"
#include "TypeToken.h"
#include "UnopToken.h"
#include "BinopToken.h"
#include "NameToken.h"

class Tokenizer {
public:
  boost::shared_ptr<Token> next(std::istream &is, SymbolTablePtr symbols);
  boost::shared_ptr<Token> peek(std::istream &is, SymbolTablePtr symbols);
};

typedef boost::shared_ptr<Token> (*TokenParsingFunc)(std::istream &is, SymbolTablePtr symbols);

const TokenParsingFunc TOKEN_PARSING_FUNCS[] ={
  &AssignToken::parse,
  &ParenToken::parse,
  &StringToken::parse,
  &UnopToken::parse,
  &BinopToken::parse,
  &TypeToken::parse,
  &NameToken::parse,
  &FloatToken::parse,
  &IntToken::parse
};

const size_t TOKEN_PARSING_FUNCS_LENGTH = sizeof(TOKEN_PARSING_FUNCS) /
  sizeof(TOKEN_PARSING_FUNCS[0]);


#endif

