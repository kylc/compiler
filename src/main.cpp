#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

#include "token/Tokenizer.h"
#include "parse/Parser.h"

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
  }

  for(int i = 1; i < argc; i++) {
    std::fstream fs(argv[i], std::fstream::in);

    if(!fs) {
      std::cerr << "Unable to open file" << std::endl;
      return 1;
    }

    Tokenizer tokenizer;
    Parser parser(fs, tokenizer);
    parser.parse().print(0);

    fs.close();
  }

  return 0;
}

