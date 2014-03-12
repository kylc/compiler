#define BOOST_ALL_DYN_LINK

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
      BOOST_LOG_TRIVIAL(fatal) << "Unable to open file";
      return EXIT_FAILURE;
    }

    Tokenizer tokenizer;
    Parser parser(fs, tokenizer);

    Node *root = parser.parse();
    root->printTree();

    std::cout << root->emitTree() << std::endl;

    fs.close();
  }

  return EXIT_SUCCESS;
}

