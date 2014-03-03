#ifndef _CONST_NODE_H
#define _CONST_NODE_H

#include <boost/shared_ptr.hpp>

#include "tree/ExprNode.h"
#include "token/Token.h"

class ConstNode : public ExprNode {
public:
  ConstNode(boost::shared_ptr<Token> token, Type type);

  virtual void print();
  virtual std::string emit();
  virtual Type getType();

private:
  boost::shared_ptr<Token> token;
  Type type;
};

#endif
