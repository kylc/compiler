#include "tree/PrintNode.h"

void PrintNode::print() {
  std::cout << "PrintNode" << std::endl;
}

std::string PrintNode::emit() {
  switch(children[0]->getType()) {
    case Type::Bool:
    case Type::Int:
      return ".s";
    case Type::Float:
      return "f.s";
    case Type::String:
      return "2dup type";
  }
}
