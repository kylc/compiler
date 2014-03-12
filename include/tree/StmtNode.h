#ifndef _STMT_NODE_H_
#define _STMT_NODE_H_

#include "tree/Node.h"

class StmtNode : public Node {
  virtual void print();
  virtual std::string emit();
};

#endif
