#include "tree/UnopNode.h"

std::map<std::string, std::string> UnopNode::UNOP_TRANSLATION_TABLE = {
  {"not", "invert"},
  {"sin", "sin"},
  {"cos", "cos"},
  {"tan", "tan"}
};

UnopNode::UnopNode(boost::shared_ptr<UnopToken> token) : token(token) {
}

void UnopNode::print() {
  std::cout << "UnopNode (" << token->getText() << ", " << getType() << ")" << std::endl;
}

std::string UnopNode::emitTree() {
  std::string l = children[0]->emitTree();

  if(getType() == Type::Float) {
    if(children[0]->getType() == Type::Int) {
      l += " s>f";
    }
  }

  return l + " " + emit() + " ";
}

std::string UnopNode::emit() {
  switch(getType()) {
    case Type::Bool:
    case Type::Int:
      return UNOP_TRANSLATION_TABLE[token->getText()];
    case Type::Float:
      return "f" + UNOP_TRANSLATION_TABLE[token->getText()];
    case Type::String:
      return "ERROR";
  }
}

Type UnopNode::getType() {
  return children[0]->getType();
}
