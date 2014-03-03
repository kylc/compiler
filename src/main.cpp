#include <fstream>
#include <iostream>

#include "token/Tokenizer.h"
#include "parse/Parser.h"
#include "tree/Node.h"

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

    Node *root = parser.parse();
    root->printTree();

    std::cout << root->emitTree() << std::endl;

    fs.close();
  }

  return 0;
}

