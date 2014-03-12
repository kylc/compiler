#ifndef _PRINT_NODE_H_
#define _PRINT_NODE_H_

#include "tree/StmtNode.h"

class PrintNode : public StmtNode {
  virtual void print();
  virtual std::string emit();
};

#endif
