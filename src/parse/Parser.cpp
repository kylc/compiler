#include "parse/Parser.h"

#include "tree/ExprNode.h"
#include "tree/IfNode.h"
#include "tree/LetNode.h"
#include "tree/OperNode.h"
#include "tree/PrintNode.h"
#include "tree/StmtNode.h"
#include "tree/VarNode.h"
#include "tree/WhileNode.h"

Parser::Parser(std::istream &stream, Tokenizer tokenizer) : stream(stream), tokenizer(tokenizer), symbols(boost::shared_ptr<SymbolTable>(new SymbolTable())) {
}

Node Parser::parse() {
  Node root;

  T(root);

  return root;
}

void Parser::T(Node &parent) {
  std::cout << "T" << std::endl;
  Node *node = new Node();
  parent.addChild(node);

  expect(typeid(ParenToken), ParenToken::Left);
  S(*node);
  expect(typeid(ParenToken), ParenToken::Right);
}

void Parser::S(Node &parent) {
  std::cout << "S" << std::endl;

  Node *node = new Node();
  parent.addChild(node);

  boost::shared_ptr<Token> p = tokenizer.peek(stream, symbols);
  if(peek(typeid(AssignToken)) ||
      peek(typeid(BinopToken)) ||
      peek(typeid(UnopToken)) ||
      peek(typeid(NameToken)) ||
      peek(typeid(IntToken)) ||
      peek(typeid(FloatToken)) ||
      peek(typeid(StringToken)) ||
      p->getText() == "if" ||
      p->getText() == "while" ||
      p->getText() == "stdout" ||
      p->getText() == "let") {
    expr(*node);

    p = tokenizer.peek(stream, symbols);
    if(peek(typeid(AssignToken)) ||
        peek(typeid(BinopToken)) ||
        peek(typeid(UnopToken)) ||
        peek(typeid(NameToken)) ||
        peek(typeid(IntToken)) ||
        peek(typeid(FloatToken)) ||
        peek(typeid(StringToken)) ||
        p->getText() == "if" ||
        p->getText() == "while" ||
        p->getText() == "stdout" ||
        p->getText() == "let") {
      S(*node);
    }

    // Check for another S for S -> SS
    if(peek(typeid(ParenToken), ParenToken::Left)) {
      S(*node);
    }

    return;
  }
  if(peek(typeid(ParenToken), ParenToken::Left)) {
    expect(typeid(ParenToken), ParenToken::Left);
    if(peek(typeid(ParenToken), ParenToken::Right)) {
      expect(typeid(ParenToken), ParenToken::Right);
      // [ ]
      // Check for another S for S -> SS
      if(peek(typeid(ParenToken), ParenToken::Left)) {
        S(*node);
      }

      return;
    } else {
      // [ S ]
      S(*node);

      expect(typeid(ParenToken), ParenToken::Right);

      // Check for another S for S -> SS
      if(peek(typeid(ParenToken), ParenToken::Left)) {
        S(*node);
        return;
      }

      return;
    }
  }

  std::cerr << "Expected S, none found" << std::endl;
  exit(0);
  return;
}

void Parser::expr(Node &parent) {
  std::cout << "expr" << std::endl;

  ExprNode *node = new ExprNode();
  parent.addChild(node);

  boost::shared_ptr<Token> p = tokenizer.peek(stream, symbols);
  if(p->getText() == "if" ||
      p->getText() == "while" ||
      p->getText() == "stdout" ||
      p->getText() == "let") {
    // stmts
    stmts(*node);

    return;
  } else if(peek(typeid(AssignToken)) ||
      peek(typeid(BinopToken)) ||
      peek(typeid(UnopToken)) ||
      peek(typeid(NameToken)) ||
      peek(typeid(IntToken)) ||
      peek(typeid(FloatToken)) ||
      peek(typeid(StringToken)) ||
      peek(typeid(ParenToken), ParenToken::Left)) {
    oper(*node);

    return;
  }

  std::cerr << "Expected statement or oper, none found" << std::endl;
  exit(0);
}

void Parser::oper(Node &parent) {
  std::cout << "oper" << std::endl;

  OperNode *node = new OperNode();
  parent.addChild(node);

  bool consumeEndParen = false;
  if(peek(typeid(ParenToken), ParenToken::Left)) {
    expect(typeid(ParenToken), ParenToken::Left);
    consumeEndParen = true;
  }
  
  // constants
  if(peek(typeid(StringToken))) {
    expect(typeid(StringToken));
    return;
  } else if(peek(typeid(IntToken))) {
    expect(typeid(IntToken));
    return;
  } else if(peek(typeid(FloatToken))) {
    expect(typeid(FloatToken));
    return;
  }
  
  // name
  else if(peek(typeid(NameToken))) {
    expect(typeid(NameToken));
    return;
  }

  else if(lastToken->getText() == "[") {
    // assign
    if(peek(typeid(AssignToken))) {
      expect(typeid(AssignToken));
      expect(typeid(NameToken));
      oper(*node);
    }

    // binop
    if(peek(typeid(BinopToken))) {
      expect(typeid(BinopToken));
      oper(*node);
      oper(*node);
    }
    
    // unop
    if(peek(typeid(UnopToken))) {
      expect(typeid(UnopToken));
      oper(*node);
    }

    if(!peek(typeid(ParenToken), ParenToken::Right)) {
      std::cerr << "Expected right paren" << std::endl;
      exit(0);
    } else {
      if(consumeEndParen) {
        expect(typeid(ParenToken), ParenToken::Right);
      }
    }

    return;
  }
  
  std::cerr << "Expected oper, none found" << std::endl;
  exit(0);
}

void Parser::stmts(Node &parent) {
  std::cout << "stmts" << std::endl;

  boost::shared_ptr<Token> token = expect(typeid(NameToken));
  boost::shared_ptr<NameToken> name = boost::dynamic_pointer_cast<NameToken>(token);

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
    expect(typeid(ParenToken), ParenToken::Left);
    varlist(*node);
    expect(typeid(ParenToken), ParenToken::Right);
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

  std::cerr << "Expected statement, none found" << std::endl;
  exit(0);
}

void Parser::exprlist(Node &parent) {
  std::cout << "exprlist" << std::endl;

  ExprNode *first = new ExprNode();
  expr(*first);
  parent.addChild(first);

  while(peek(typeid(BinopToken)) ||
     peek(typeid(UnopToken)) ||
     peek(typeid(StringToken)) ||
     peek(typeid(IntToken)) ||
     peek(typeid(FloatToken)) ||
     peek(typeid(NameToken))) {
    ExprNode *next = new ExprNode();
    expr(*next);
    parent.addChild(next);
  }

  return;
}

void Parser::varlist(Node &parent) {
  std::cout << "varlist" << std::endl;

  VarNode *first = new VarNode();
  expect(typeid(ParenToken), ParenToken::Left);
  expect(typeid(NameToken));
  expect(typeid(TypeToken));
  expect(typeid(ParenToken), ParenToken::Right);
  parent.addChild(first);

  if(peek(typeid(ParenToken), ParenToken::Left)) {
    varlist(parent);
  }
}

bool Parser::peek(const std::type_info &type) {
  // std::cout << "Peeking: " << type.name() << std::endl;
  boost::shared_ptr<Token> next = tokenizer.peek(stream, symbols);
  if(typeid(*next) != type) {
    return false;
  }
  return true;
}

bool Parser::peek(const std::type_info &type, unsigned int subtype) {
  // std::cout << "Peeking: " << type.name() << std::endl;
  boost::shared_ptr<Token> next = tokenizer.peek(stream, symbols);
  if(typeid(*next) != type || next->getType() != subtype) {
    return false;
  }
  return true;
}

boost::shared_ptr<Token> Parser::expect(const std::type_info &type) {
  lastToken = tokenizer.next(stream, symbols);
  std::string text = lastToken == NULL ? "NULL" : lastToken->getText();
  std::cout << "Consuming: " << type.name() << " " << text << std::endl;
  if(lastToken == NULL || typeid(*lastToken) != type) {
    std::string got = lastToken == NULL ? "NULL" : typeid(*lastToken).name();
    std::cerr << "Expected '" << type.name() << "' got '" << got << "'" << std::endl;
    exit(0);
  }

  return lastToken;
}

boost::shared_ptr<Token> Parser::expect(const std::type_info &type, unsigned int subtype) {
  lastToken = tokenizer.next(stream, symbols);
  std::string text = lastToken == NULL ? "NULL" : lastToken->getText();
  std::cout << "Consuming: " << type.name() << " " << text << std::endl;
  if(lastToken == NULL || typeid(*lastToken) != type || lastToken->getType() != subtype) {
    std::string got = lastToken == NULL ? "NULL" : typeid(*lastToken).name();
    std::cerr << "Expected '" << type.name() << "' " << subtype << " got '" << got << "'" << std::endl;
    std::cerr << "Expected '" << type.name() << "' " << subtype << " got '" << got << "' " << lastToken->getType() << std::endl;
    exit(0);
  }

  return lastToken;
}
