#include "token/Tokenizer.h"

boost::shared_ptr<Token> Tokenizer::next(std::fstream &fs) {
  for(size_t i = 0; i < TOKEN_PARSING_FUNCS_LENGTH; i++) {
    std::streampos pos = fs.tellg();

    TokenParsingFunc f = TOKEN_PARSING_FUNCS[i];
    boost::shared_ptr<Token> token = f(fs);

    if(token) {
      return token;
    } else {
      fs.seekg(pos);
    }
  }

  std::cerr << "Compiler error!" << std::endl;
  exit(0);

  return NULL;
}

