#ifndef _ROOT_NODE_H
#define _ROOT_NODE_H

#include "tree/Node.h"

class RootNode : public Node {
  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
};

#endif
