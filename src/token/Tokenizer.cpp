#include "token/Tokenizer.h"

boost::shared_ptr<Token> Tokenizer::next(std::istream &is, SymbolTablePtr symbols) {
  // Clear any whitespace until the next token. This works because no token
  // depends on _leading_ whitespace, as long as it is separated from the
  // previous token.
  while(std::isspace(is.peek())) is.get();

  // Now that we've cleared whitespace, may be at EOF.
  if(!is.good()) return NULL;

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

  std::cerr << "Tokenizer error!" << std::endl;
  exit(0);

  return NULL;
}

// TODO: fix
boost::shared_ptr<Token> Tokenizer::peek(std::istream &is, SymbolTablePtr symbols) {
  std::streampos pos = is.tellg();
  boost::shared_ptr<Token> peek = next(is, symbols);
  is.seekg(pos);

  return peek;
}
