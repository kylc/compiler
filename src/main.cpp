#include "token/Tokenizer.h"

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
    // Clear any whitespace until the next token. This works because no token
    // depends on _leading_ whitespace, as long as it is separated from the
    // previous token.
    while(std::isspace(fs.peek())) fs.get();

    // Now that we've cleared whitespace, may be at EOF.
    if(!fs.good()) break;

    boost::shared_ptr<Token> next = tokenizer.next(fs);
    if(next) {
      std::cout << "<" << next->getTagName() << ", " << next->getText() << "> ";
    }
  }

  std::cout << std::endl;

  fs.close();

  return 0;
}

