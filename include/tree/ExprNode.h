#ifndef _EXPR_NODE_H
#define _EXPR_NODE_H

#include "tree/Node.h"

class ExprNode : public Node {
  virtual void print();
  virtual std::string emit();
};

#endif
