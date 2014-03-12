#include "tree/LetNode.h"

#include "tree/VarNode.h"

#include <sstream>

void LetNode::print() {
  std::cout << "LetNode" << std::endl;
}

std::string LetNode::emitTree() {
  std::stringstream ss;

  // Push default values onto stack
  for(Node *child : children) {
    VarNode *vnode = dynamic_cast<VarNode *>(child);
    ss << vnode->getDefaultValue() + " ";
  }

  // Variable declarations
  ss << "{ ";
  for(Node *child : children) {
    VarNode *vnode = dynamic_cast<VarNode *>(child);
    std::string varname = vnode->getName();

    // Declare in parent of LetNode scope rather than parent of VarNode scope
    // (which would be this LetNode).
    Variable *var = new Variable(vnode->getType());
    variables->insertToParent(varname, var);

    ss << child->emit() << " ";
  }
  ss << "} ";


  return ss.str();
}
