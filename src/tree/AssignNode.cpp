#include "tree/AssignNode.h"

#include <boost/log/trivial.hpp>

AssignNode::AssignNode(boost::shared_ptr<NameToken> name) : name(name) {
}

void AssignNode::print() {
  std::cout << "AssignNode" << std::endl;
}

std::string AssignNode::emitTree() {
  std::string varname = name->getText();
  Variable *var = variables->lookup(varname);

  if(children[0]->getType() != var->getType()) {
    BOOST_LOG_TRIVIAL(warning) << "Assigning wrong type to variable";
  }

  return children[0]->emitTree() + " TO " + varname + " ";
}
