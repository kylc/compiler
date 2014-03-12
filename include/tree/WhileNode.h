#ifndef _WHILE_NODE_H_
#define _WHILE_NODE_H_

#include "tree/StmtNode.h"

class WhileNode : public StmtNode {
  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
};

#endif
