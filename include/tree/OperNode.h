#ifndef _OPER_NODE_H
#define _OPER_NODE_H

#include "tree/Node.h"

class OperNode : public Node {
  virtual void printNode();
  virtual std::string emit();
};

#endif
