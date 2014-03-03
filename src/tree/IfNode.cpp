#include "tree/IfNode.h"

void IfNode::print() {
  std::cout << "IfNode" << std::endl;
}

std::string IfNode::emitTree() {
  // condition
  std::string b = children[0]->emitTree();

  // if
  b += "if " + children[1]->emitTree();

  if(children.size() > 2) {
    // else
    b += " else " + children[2]->emitTree();
  }

  b += "then ";

  return b;
}

std::string IfNode::emit() {
  return "if";
}
