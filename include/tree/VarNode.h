#ifndef _VAR_NODE_H
#define _VAR_NODE_H

#include "tree/Node.h"

#include <boost/shared_ptr.hpp>

#include "token/NameToken.h"
#include "token/TypeToken.h"

class VarNode : public Node {
public:
  VarNode(boost::shared_ptr<NameToken> name, boost::shared_ptr<TypeToken> type);

  virtual void print();
  virtual std::string emit();
  virtual Type getType();

  std::string getName();
  std::string getDefaultValue();

private:
  boost::shared_ptr<NameToken> name;
  boost::shared_ptr<TypeToken> type;
};

#endif
