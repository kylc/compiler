#include "tree/VarNode.h"

VarNode::VarNode(boost::shared_ptr<NameToken> name, boost::shared_ptr<TypeToken> type) : name(name), type(type) {
}

void VarNode::print() {
  std::cout << "VarNode (" << name->getText() << ")" << std::endl;
}

std::string VarNode::emit() {
  std::string tname = type->getText();

  std::string outtype;
  switch(getType()) {
    case Type::Float:
      outtype = "F: ";
      break;
    case Type::Int:
    case Type::Bool:
      outtype = "W: ";
      break;
    default:
      throw std::runtime_error("Invalid variable type");
  }

  return outtype + name->getText();
}

std::string VarNode::getName() {
  return name->getText();
}

Type VarNode::getType() {
  std::string tname = type->getText();

  if(tname == "float") {
    return Type::Float;
  } else if(tname == "int") {
    return Type::Int;
  } else if(tname == "bool") {
    return Type::Bool;
  } else if(tname == "string") {
    return Type::String;
  } else {
    throw std::runtime_error("Invalid variable type");
  }
}

std::string VarNode::getDefaultValue() {
  std::string tname = type->getText();

  if(tname == "float") {
    return "0e0";
  } else if(tname == "int") {
    return "0";
  } else if(tname == "bool") {
    return "false";
  } else {
    throw std::runtime_error("Invalid variable type");
  }
}
