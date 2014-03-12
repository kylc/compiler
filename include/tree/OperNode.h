#ifndef _OPER_NODE_H_
#define _OPER_NODE_H_

#include "tree/Node.h"

class OperNode : public Node {
  virtual void print();
  virtual std::string emit();
};

#endif
