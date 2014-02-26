#ifndef _STMT_NODE_H
#define _STMT_NODE_H

#include "tree/Node.h"

class StmtNode : public Node {
  virtual void printNode();
  virtual std::string emit();
};

#endif
