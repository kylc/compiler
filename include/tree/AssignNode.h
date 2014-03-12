#ifndef _ASSIGN_NODE_H
#define _ASSIGN_NODE_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "token/NameToken.h"
#include "tree/OperNode.h"

class AssignNode : public OperNode {
public:
  AssignNode(boost::shared_ptr<NameToken> name);

  virtual void print();
  virtual std::string emitTree();

private:
  boost::shared_ptr<NameToken> name;
};

#endif
