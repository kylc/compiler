#ifndef _VAR_ACCESS_NODE_H
#define _VAR_ACCESS_NODE_H

#include <boost/shared_ptr.hpp>

#include "tree/ExprNode.h"
#include "token/NameToken.h"

class VarAccessNode : public ExprNode {
public:
  VarAccessNode(boost::shared_ptr<NameToken> name);

  virtual void print();
  virtual std::string emit();
  virtual Type getType();

private:
  boost::shared_ptr<Token> name;
};

#endif
