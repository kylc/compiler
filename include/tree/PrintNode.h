#ifndef _PRINT_NODE_H
#define _PRINT_NODE_H

#include "tree/StmtNode.h"

class PrintNode : public StmtNode {
  virtual void print();
  virtual std::string emit();
};

#endif