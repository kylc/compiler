#include "tree/BinopNode.h"

#include <sstream>
#include <boost/log/trivial.hpp>

std::map<std::string, std::string> BinopNode::BINOP_TRANSLATION_TABLE = {
  {"+", "+"},
  {"-", "-"},
  {"*", "*"},
  {"/", "/"},
  {"%", "mod"},
  {"^", "**"},
  {"=", "="},
  {">", ">"},
  {">=", ">="},
  {"<", "<"},
  {"<=", "<="},
  {"!=", "<>"},
  {"or", "or"},
  {"and", "and"},
};

std::map<std::string, std::string> BinopNode::BINOP_STRING_TRANSLATION_TABLE = {
  {"+", "append"}
};

BinopNode::BinopNode(boost::shared_ptr<BinopToken> token) : token(token) {
}

void BinopNode::print() {
  std::cout << "BinopNode (" << token->getText() << ")" << std::endl;
}

std::string BinopNode::emitTree() {
  std::string l = children[0]->emitTree();
  std::string r = children[1]->emitTree();

  if(getType() == Type::Float) {
    if(children[0]->getType() == Type::Int) {
      l += " s>f";
    }

    if(children[1]->getType() == Type::Int) {
      r += " s>f";
    }
  }

  return l + " " + r + " " + emit() + " ";
}

std::string BinopNode::emit() {
  if(children[0]->getType() != children[1]->getType()) {
    // Handle corner-case of int->float upcast
    if((children[0]->getType() != Type::Int && children[0]->getType() != Type::Float) ||
       (children[1]->getType() != Type::Int && children[1]->getType() != Type::Float)) {
      BOOST_LOG_TRIVIAL(warning) << "Invalid type comparison on binop " << token->getText();
    }
  }

  switch(getMaxType()) {
    case Type::Bool:
    case Type::Int:
      return BINOP_TRANSLATION_TABLE[token->getText()];
    case Type::Float:
      return "f" + BINOP_TRANSLATION_TABLE[token->getText()];
    case Type::String:
      return BINOP_STRING_TRANSLATION_TABLE[token->getText()];
  }

  throw std::runtime_error("Invalid type on Binop");
}

Type BinopNode::getType() {
  switch(token->getType()) {
    case BinopToken::Equal:
    case BinopToken::Neq:
    case BinopToken::Less:
    case BinopToken::Greater:
    case BinopToken::Leq:
    case BinopToken::Geq:
      return Type::Bool;
  }

  return getMaxType();
}

Type BinopNode::getMaxType() {
  // string concatenation
  if(children[0]->getType() == Type::String && children[1]->getType() == Type::String) {
    if(token->getType() == BinopToken::Plus) {
      return Type::String;
    }
  }

  if(children[0]->getType() == Type::Float || children[1]->getType() == Type::Float) {
    return Type::Float;
  } else if(children[0]->getType() == Type::Int || children[1]->getType() == Type::Int) {
    return Type::Int;
  } else if(children[0]->getType() == Type::Bool || children[1]->getType() == Type::Bool) {
    return Type::Bool;
  } else if(children[0]->getType() == Type::String || children[1]->getType() == Type::String) {
    return Type::String;
  }

  throw std::runtime_error("Invalid types");
}
