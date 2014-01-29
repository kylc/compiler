#include "Tokenizer.h"

boost::shared_ptr<Token> ParenToken::parse(std::fstream &fs) {
  char next = fs.get();
  std::string s(1, next);

  boost::shared_ptr<Token> token = NULL;
  if(next == '[') {
    token = boost::shared_ptr<Token>(new ParenToken(s));
  } else if(next == ']') {
    token = boost::shared_ptr<Token>(new ParenToken(s));
  }

  return token;
}

boost::shared_ptr<Token> StringToken::parse(std::fstream &fs) {
  std::string value;

  int state = 0;
  while(true) {
    char next = fs.get();

    switch(state) {
      case 0:
        if(next == '"') {
          state = 1;
        } else {
          state = ERROR_STATE;
        }
        break;
      case 1:
        if(next == '"') {
          return boost::shared_ptr<Token>(new StringToken(value));
        } else if(std::isalnum(next) || std::isspace(next)) {
          value += next;
        } else {
          state = ERROR_STATE;
        }
        break;
      case ERROR_STATE:
        return NULL;
    }
  }
}

boost::shared_ptr<Token> IntToken::parse(std::fstream &fs) {
  std::string value;

  int state = 0;
  while(true) {
    char next = fs.get();

    switch(state) {
      case 0:
        if(next == '+' || next == '-' || std::isdigit(next)) {
          state = 1;
          value += next;
        } else {
          state = ERROR_STATE;
        }
        break;
      case 1:
        if(std::isdigit(next)) {
          state = 1;
          value += next;
        } else {
          fs.putback(next);
          return boost::shared_ptr<Token>(new IntToken(value));
        }
        break;
      case ERROR_STATE:
        return NULL;
    }
  }
}

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

  return NULL;
}

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
  }

  std::fstream fs(argv[1], std::fstream::in);

  if(!fs) {
    std::cerr << "Unable to open file" << std::endl;
    return 1;
  }

  Tokenizer tokenizer;
  while(fs.good()) {
    while(fs.peek() == '\n') fs.get();
    while(fs.peek() == ' ') fs.get();

    boost::shared_ptr<Token> next = tokenizer.next(fs);
    if(next) {
      std::cout << "<" << next->getTagName() << ", " << next->getValue() << "> ";
    }
  }

  std::cout << std::endl;

  fs.close();

  return 0;
}
