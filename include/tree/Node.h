#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
public:
  Node();

  void addChild(Node *node);

  void printTree(int indent = 0);
  virtual void print();

  void emitTree();
  virtual std::string emit();

protected:
  std::vector<Node*> children;
};

#endif
