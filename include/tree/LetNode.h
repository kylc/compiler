#ifndef _LET_NODE_H_
#define _LET_NODE_H_

#include "tree/StmtNode.h"

class LetNode : public StmtNode {
  virtual void print();
  virtual std::string emitTree();
};

#endif
