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

void Node::emitTree() {
  for(Node *child : children) {
    child->emit();
  }

  emit();
}

std::string Node::emit() {
  return "NOTHING";
}
