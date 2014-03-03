#ifndef _BINOP_NODE_H
#define _BINOP_NODE_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "tree/OperNode.h"
#include "token/BinopToken.h"


class BinopNode : public OperNode {
public:
  BinopNode(boost::shared_ptr<BinopToken> token);

  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
  virtual Type getType();
  Type getMaxType();

private:
  static std::map<std::string, std::string> BINOP_TRANSLATION_TABLE;
  static std::map<std::string, std::string> BINOP_STRING_TRANSLATION_TABLE;
  boost::shared_ptr<BinopToken> token;
};

#endif
