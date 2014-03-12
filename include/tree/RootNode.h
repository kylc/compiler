#ifndef _ROOT_NODE_H_
#define _ROOT_NODE_H_

#include "tree/Node.h"

class RootNode : public Node {
  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
};

#endif
