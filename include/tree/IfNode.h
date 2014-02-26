#ifndef _IF_NODE_H
#define _IF_NODE_H

#include "tree/StmtNode.h"

class IfNode : public StmtNode {
  virtual void printNode();
  virtual std::string emit();
};

#endif
