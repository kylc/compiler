#include "parse/Parser.h"

#include "tree/BinopNode.h"
#include "tree/ConstNode.h"
#include "tree/ExprNode.h"
#include "tree/IfNode.h"
#include "tree/LetNode.h"
#include "tree/OperNode.h"
#include "tree/PrintNode.h"
#include "tree/RootNode.h"
#include "tree/StmtNode.h"
#include "tree/UnopNode.h"
#include "tree/VarNode.h"
#include "tree/WhileNode.h"
#include "util/Util.h"

Parser::Parser(std::istream &stream, Tokenizer tokenizer) : stream(stream), tokenizer(tokenizer), symbols(boost::shared_ptr<SymbolTable>(new SymbolTable())) {
}

Node *Parser::parse() {
  RootNode *root = new RootNode();

  T(*root);

  return root;
}

void Parser::T(Node &parent) {
  std::cout << "T" << std::endl;

  expect<ParenToken>(ParenToken::Left);
  S(parent);
  expect<ParenToken>(ParenToken::Right);
}

void Parser::S(Node &parent) {
  std::cout << "S" << std::endl;

  boost::shared_ptr<Token> p = tokenizer.peek(stream, symbols);
  if(peek<AssignToken>() ||
      peek<BinopToken>() ||
      peek<UnopToken>() ||
      peek<NameToken>() ||
      peek<IntToken>() ||
      peek<FloatToken>() ||
      peek<StringToken>() ||
      peek<BoolToken>() ||
      p->getText() == "if" ||
      p->getText() == "while" ||
      p->getText() == "stdout" ||
      p->getText() == "let") {
    expr(parent);

    p = tokenizer.peek(stream, symbols);
    if(peek<AssignToken>() ||
        peek<BinopToken>() ||
        peek<UnopToken>() ||
        peek<NameToken>() ||
        peek<IntToken>() ||
        peek<FloatToken>() ||
        peek<StringToken>() ||
        peek<BoolToken>() ||
        p->getText() == "if" ||
        p->getText() == "while" ||
        p->getText() == "stdout" ||
        p->getText() == "let") {
      S(parent);
    }

    // Check for another S for S -> SS
    if(peek<ParenToken>(ParenToken::Left)) {
      S(parent);
    }

    return;
  }
  if(peek<ParenToken>(ParenToken::Left)) {
    expect<ParenToken>(ParenToken::Left);
    if(peek<ParenToken>(ParenToken::Right)) {
      expect<ParenToken>(ParenToken::Right);
      // [ ]
      // Check for another S for S -> SS
      if(peek<ParenToken>(ParenToken::Left)) {
        S(parent);
      }

      return;
    } else {
      // [ S ]
      S(parent);

      expect<ParenToken>(ParenToken::Right);

      // Check for another S for S -> SS
      if(peek<ParenToken>(ParenToken::Left)) {
        S(parent);
        return;
      }

      return;
    }
  }

  fail("Expected S, none found");
}

void Parser::expr(Node &parent) {
  std::cout << "expr" << std::endl;

  bool consumeEndParen = false;
  if(peek<ParenToken>(ParenToken::Left)) {
    expect<ParenToken>(ParenToken::Left);
    consumeEndParen = true;
  }
  
  boost::shared_ptr<Token> p = tokenizer.peek(stream, symbols);
  std::cout << "Text: '" << p->getText() << "'" << std::endl;
  if(p->getText() == "if" ||
      p->getText() == "while" ||
      p->getText() == "stdout" ||
      p->getText() == "let") {
    // stmts
    stmts(parent);
  } else if(peek<AssignToken>() ||
      peek<BinopToken>() ||
      peek<UnopToken>() ||
      peek<NameToken>() ||
      peek<IntToken>() ||
      peek<FloatToken>() ||
      peek<StringToken>() ||
      peek<BoolToken>() ||
      peek<ParenToken>(ParenToken::Left)) {
    oper(parent);
  } else {
    fail("Expected statement or oper, none found");
  }

  if(consumeEndParen) {
    expect<ParenToken>(ParenToken::Right);
  }
}

void Parser::oper(Node &parent) {
  std::cout << "oper" << std::endl;

  bool consumeEndParen = false;
  if(peek<ParenToken>(ParenToken::Left)) {
    expect<ParenToken>(ParenToken::Left);
    consumeEndParen = true;
  }
  
  // constants
  if(peek<StringToken>()) {
    boost::shared_ptr<Token> c = expect<StringToken>();

    ConstNode *node = new ConstNode(c, Type::String);
    parent.addChild(node);

    return;
  } else if(peek<IntToken>()) {
    boost::shared_ptr<Token> c = expect<IntToken>();

    ConstNode *node = new ConstNode(c, Type::Int);
    parent.addChild(node);

    return;
  } else if(peek<FloatToken>()) {
    boost::shared_ptr<Token> c = expect<FloatToken>();

    ConstNode *node = new ConstNode(c, Type::Float);
    parent.addChild(node);

    return;
  } else if(peek<BoolToken>()) {
    boost::shared_ptr<Token> c = expect<BoolToken>();

    ConstNode *node = new ConstNode(c, Type::Bool);
    parent.addChild(node);

    return;
  }
  
  // name
  else if(peek<NameToken>()) {
    expect<NameToken>();
    return;
  }

  else if(lastToken->getText() == "[") {
    // assign
    if(peek<AssignToken>()) {
      OperNode *node = new OperNode();

      expect<AssignToken>();
      expect<NameToken>();
      oper(*node);

      parent.addChild(node);
    }

    // binop
    if(peek<BinopToken>()) {
      BinopNode *node = new BinopNode(expect<BinopToken>());

      oper(*node);
      oper(*node);

      parent.addChild(node);
    }
    
    // unop
    if(peek<UnopToken>()) {
      UnopNode *node = new UnopNode(expect<UnopToken>());

      oper(*node);

      parent.addChild(node);
    }

    if(!peek<ParenToken>(ParenToken::Right)) {
      fail("Expected right paren");
    } else {
      if(consumeEndParen) {
        expect<ParenToken>(ParenToken::Right);
      }
    }

    return;
  }
  
  fail("Expected oper, none found");
}

void Parser::stmts(Node &parent) {
  std::cout << "stmts" << std::endl;

  boost::shared_ptr<NameToken> name = expect<NameToken>();

  // ifstmt
  if(name->getText() == "if") {
    std::cout << "if" << std::endl;

    IfNode *node = new IfNode();
    expr(*node);
    expr(*node);
    expr(*node);
    parent.addChild(node);

    return;
  }

  // whilestmt
  if(name->getText() == "while") {
    std::cout << "while" << std::endl;

    WhileNode *node = new WhileNode();
    expr(*node);
    exprlist(*node);
    parent.addChild(node);

    return;
  }

  // letstmt
  if(name->getText() == "let") {
    std::cout << "let" << std::endl;

    LetNode *node = new LetNode();
    expect<ParenToken>(ParenToken::Left);
    varlist(*node);
    expect<ParenToken>(ParenToken::Right);
    parent.addChild(node);

    return;
  }

  // printstmt
  if(name->getText() == "stdout") {
    std::cout << "stdout" << std::endl;
    PrintNode *node = new PrintNode();
    oper(*node);
    parent.addChild(node);

    return;
  }

  fail("Expected statement, none found");
}

void Parser::exprlist(Node &parent) {
  std::cout << "exprlist" << std::endl;

  ExprNode *first = new ExprNode();
  expr(*first);
  parent.addChild(first);

  while(peek<BinopToken>() ||
     peek<UnopToken>() ||
     peek<StringToken>() ||
     peek<IntToken>() ||
     peek<FloatToken>() ||
     peek<NameToken>()) {
    ExprNode *next = new ExprNode();
    expr(*next);
    parent.addChild(next);
  }

  return;
}

void Parser::varlist(Node &parent) {
  std::cout << "varlist" << std::endl;

  VarNode *first = new VarNode();
  expect<ParenToken>(ParenToken::Left);
  expect<NameToken>();
  expect<TypeToken>();
  expect<ParenToken>(ParenToken::Right);
  parent.addChild(first);

  if(peek<ParenToken>(ParenToken::Left)) {
    varlist(parent);
  }
}

template<typename X>
bool Parser::peek() {
  // std::cout << "Peeking: " << type.name() << std::endl;
  boost::shared_ptr<Token> next = tokenizer.peek(stream, symbols);

  const std::type_info &type = typeid(X);
  if(typeid(*next) != type) {
    return false;
  }
  return true;
}

template<typename X>
bool Parser::peek(unsigned int subtype) {
  // std::cout << "Peeking: " << type.name() << std::endl;
  boost::shared_ptr<Token> next = tokenizer.peek(stream, symbols);

  const std::type_info &type = typeid(X);
  if(typeid(*next) != type || next->getType() != subtype) {
    return false;
  }
  return true;
}

template<typename X>
boost::shared_ptr<X> Parser::expect() {
  lastToken = tokenizer.next(stream, symbols);
  std::string text = lastToken == NULL ? "NULL" : lastToken->getText();

  const std::type_info &type = typeid(X);
  std::cout << "Consuming: " << type.name() << " " << text << std::endl;
  if(lastToken == NULL || typeid(*lastToken) != type) {
    std::string got = lastToken == NULL ? "NULL" : typeid(*lastToken).name();
    // fail("Expected '" + type.name() + "' got '" + got + "'");
  }

  return boost::static_pointer_cast<X>(lastToken);
}

template<typename X>
boost::shared_ptr<X> Parser::expect(unsigned int subtype) {
  lastToken = tokenizer.next(stream, symbols);
  std::string text = lastToken == NULL ? "NULL" : lastToken->getText();

  const std::type_info &type = typeid(X);
  std::cout << "Consuming: " << type.name() << " " << text << std::endl;
  if(lastToken == NULL || typeid(*lastToken) != type || lastToken->getType() != subtype) {
    std::string got = lastToken == NULL ? "NULL" : typeid(*lastToken).name();
    // fail("Expected '" + type.name() + "' " + subtype + " got '" + got + "' " + lastToken->getType());
  }

  return boost::static_pointer_cast<X>(lastToken);
}
