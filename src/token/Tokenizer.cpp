#include "token/Tokenizer.h"

boost::shared_ptr<Token> Tokenizer::next(std::istream &is, SymbolTablePtr symbols) {
  for(size_t i = 0; i < TOKEN_PARSING_FUNCS_LENGTH; i++) {
    std::streampos pos = is.tellg();

    TokenParsingFunc f = TOKEN_PARSING_FUNCS[i];
    boost::shared_ptr<Token> token = f(is, symbols);

    if(token) {
      return token;
    } else {
      is.seekg(pos);
    }
  }

  std::cerr << "Compiler error!" << std::endl;
  exit(0);

  return NULL;
}

