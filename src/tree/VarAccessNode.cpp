#include "tree/VarAccessNode.h"

VarAccessNode::VarAccessNode(boost::shared_ptr<NameToken> name) : name(name) {
}

void VarAccessNode::print() {
  std::cout << "VarAccessNode (" << name->getText() << ")" << std::endl;
}

std::string VarAccessNode::emit() {
  // Check that the variable exists (will throw an error otherwise).
  Variable *var = variables->lookup(name->getText());

  return name->getText();
}

Type VarAccessNode::getType() {
  Variable *var = variables->lookup(name->getText());

  return var->getType();
}
