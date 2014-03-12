#ifndef _UNOP_NODE_H_
#define _UNOP_NODE_H_

#include <map>
#include <boost/shared_ptr.hpp>

#include "tree/OperNode.h"
#include "token/UnopToken.h"


class UnopNode : public OperNode {
public:
  UnopNode(boost::shared_ptr<UnopToken> token);

  virtual void print();
  virtual std::string emitTree();
  virtual std::string emit();
  virtual Type getType();

private:
  static std::map<std::string, std::string> UNOP_TRANSLATION_TABLE;
  boost::shared_ptr<UnopToken> token;
};

#endif
