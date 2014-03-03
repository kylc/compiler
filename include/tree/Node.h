#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <string>
#include <vector>

#include "tree/Type.h"

class Node {
public:
  Node();

  void addChild(Node *node);

  void printTree(int indent = 0);
  virtual void print();

  virtual std::string emitTree();
  virtual std::string emit();

  virtual Type getType();

protected:
  std::vector<Node*> children;
};

#endif
