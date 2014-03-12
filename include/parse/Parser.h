#ifndef _PARSER_H_
#define _PARSER_H_

#include <utility>
#include <typeinfo>
#include <unordered_set>
#include <boost/shared_ptr.hpp>

#include "token/Tokenizer.h"
#include "tree/Node.h"

class Parser {
public:
  Parser(std::istream &stream, Tokenizer tokenizer);
  Node *parse();
private:
  template<typename X>
  bool peek();
  template<typename X>
  bool peek(unsigned int subtype);

  template<typename X>
  boost::shared_ptr<X> expect();
  template<typename X>
  boost::shared_ptr<X> expect(unsigned int subtype);

  void T(Node &parent);
  void S(Node &parent);
  void expr(Node &parent);
  void oper(Node &parent);
  void stmts(Node &parent);
  void exprlist(Node &parent);
  void varlist(Node &parent);

  void fail(std::string str);

  SymbolTablePtr symbols;
  std::istream &stream;
  Tokenizer tokenizer;
  boost::shared_ptr<Token> lastToken;
};

#endif
