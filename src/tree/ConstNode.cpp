#include "tree/ConstNode.h"

#include <sstream>

ConstNode::ConstNode(boost::shared_ptr<Token> token, Type type) : token(token), type(type) {
}

void ConstNode::print() {
  std::cout << "ConstNode (" << token->getText() << ", " << getType() << ")" << std::endl;
}

std::string ConstNode::emit() {
  std::stringstream ss;
  switch(getType()) {
    case Type::String:
      ss << "S\" " << token->getText() << "\"";
      return ss.str();
    case Type::Float:
      if(token->getText().find("e") == std::string::npos) {
        return token->getText() + "e0";
      }
    case Type::Bool:
    case Type::Int:
      return token->getText();
  }
}

Type ConstNode::getType() {
  return type;
}
