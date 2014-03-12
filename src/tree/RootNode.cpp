#include "tree/RootNode.h"

void RootNode::print() {
  std::cout << "RootNode" << std::endl;
}

std::string RootNode::emitTree() {
  std::string out = ": compiled-main ";

  for(Node *child : children) {
    out += child->emitTree();
  }

  out += emit() + " ";

  return out + "; compiled-main ";
}

std::string RootNode::emit() {
  return "";
}
