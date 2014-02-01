#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <boost/shared_ptr.hpp>
#include <fstream>

#include "Token.h"
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
  boost::shared_ptr<Token> next(std::fstream &fs);
};

typedef boost::shared_ptr<Token> (*TokenParsingFunc)(std::fstream &fs);

const TokenParsingFunc TOKEN_PARSING_FUNCS[] ={
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

