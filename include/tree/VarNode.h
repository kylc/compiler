#ifndef _VAR_NODE_H
#define _VAR_NODE_H

#include "tree/Node.h"

class VarNode : public Node {
  virtual void print();
  virtual std::string emit();
};

#endif
