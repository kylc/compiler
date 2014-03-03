#include "tree/RootNode.h"

void RootNode::print() {
  std::cout << "RootNode" << std::endl;
}

std::string RootNode::emitTree() {
  std::string out = ": root ";

  for(Node *child : children) {
    out += child->emitTree();
  }

  out += emit() + " ";

  return out + "; root";
}

std::string RootNode::emit() {
  return "";
}
