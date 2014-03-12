#ifndef _EXPR_NODE_H_
#define _EXPR_NODE_H_

#include "tree/Node.h"

class ExprNode : public Node {
  virtual void print();
  virtual std::string emit();
};

#endif
