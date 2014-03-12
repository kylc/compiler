#include "tree/AssignNode.h"

AssignNode::AssignNode(boost::shared_ptr<NameToken> name) : name(name) {
}

void AssignNode::print() {
  std::cout << "AssignNode" << std::endl;
}

std::string AssignNode::emitTree() {
  std::string varname = name->getText();

  return children[0]->emitTree() + " TO " + varname + " ";
}
