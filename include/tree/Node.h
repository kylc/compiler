#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
public:
  Node() { }

  void addChild(Node *node) {
    children.push_back(node);
  }

  void print(int indent) {
    for(int i = 0; i < indent; i++) {
      std::cout << " ";
    }

    printNode();

    for(int i = 0; i < children.size(); i++) {
      children[i]->print(indent + 1);
    }
  }

  virtual void printNode() {
    std::cout << "Node" << std::endl;
  }

  void emitTree() {
    for(int i = 0; i < children.size(); i++) {
      children[i]->emit();
    }

    emit();
  }

  virtual std::string emit() {
    return "NOTHING";
  }

protected:
  std::vector<Node*> children;
};

#endif
