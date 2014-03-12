#ifndef _IF_NODE_H_
#define _IF_NODE_H_

#include "tree/StmtNode.h"

class IfNode : public StmtNode {
  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
};

#endif
