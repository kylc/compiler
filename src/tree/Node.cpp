#include "tree/Node.h"


Node::Node() { }

void Node::addChild(Node *node) {
  children.push_back(node);
}

void Node::printTree(int indent) {
  for(int i = 0; i < indent; i++) {
    std::cout << " ";
  }

  print();

  for(int i = 0; i < children.size(); i++) {
    children[i]->printTree(indent + 1);
  }
}

void Node::print() {
  std::cout << "Node" << std::endl;
}

void Node::emitTree() {
  for(int i = 0; i < children.size(); i++) {
    children[i]->emit();
  }

  emit();
}

std::string Node::emit() {
  return "NOTHING";
}
