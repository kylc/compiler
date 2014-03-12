#ifndef _WHILE_NODE_H
#define _WHILE_NODE_H

#include "tree/StmtNode.h"

class WhileNode : public StmtNode {
  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
};

#endif
