#ifndef _WHILE_NODE_H
#define _WHILE_NODE_H

#include "tree/StmtNode.h"

class WhileNode : public StmtNode {
  virtual void printNode();
  virtual std::string emit();
};

#endif
