#include "tree/Node.h"


Node::Node() { }

void Node::addChild(Node *node) {
  children.push_back(node);
}

void Node::printTree(int indent) {
  for(unsigned int i = 0; i < indent; i++) {
    std::cout << " ";
  }

  print();

  for(Node *child : children) {
    child->printTree(indent + 1);
  }
}

void Node::print() {
  std::cout << "Node" << std::endl;
}

std::string Node::emitTree() {
  std::string out = "";

  for(Node *child : children) {
    out += child->emitTree();
  }

  out += emit() + " ";

  return out;
}

std::string Node::emit() {
  return "";
}

Type Node::getType() {
  std::cerr << "FAIL!" << std::endl;
  exit(0);
}
