#include "tree/WhileNode.h"

void WhileNode::print() {
  std::cout << "WhileNode" << std::endl;
}

std::string WhileNode::emitTree() {
  std::string out = "BEGIN ";

  Node *flag = children[0];
  
  for(unsigned int i = 1; i < children.size(); i++) {
    out += children[i]->emitTree();
  }

  // Invert the loop condition. IBTL defines a while(flag) loop, but we emit an
  // until(flag) loop.
  out += flag->emitTree() + "invert ";
  out += "UNTIL ";

  return out;
}

std::string WhileNode::emit() {
  return "";
}
