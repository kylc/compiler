#ifndef _LET_NODE_H
#define _LET_NODE_H

#include "tree/StmtNode.h"

class LetNode : public StmtNode {
  virtual void printNode();
  virtual std::string emit();
};

#endif
