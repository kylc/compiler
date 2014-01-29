#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <boost/shared_ptr.hpp>
#include <fstream>

class Token {
public:
  Token(std::string value) : value(value) {}

  std::string getValue() { return value; }

  virtual std::string getTagName() = 0;

private:
  std::string value;
};

class ParenToken : public Token {
public:
  ParenToken(std::string value) : Token(value) {}

  std::string getTagName() { return "PAREN"; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);
};

class StringToken : public Token {
public:
  StringToken(std::string value) : Token(value) {}

  std::string getTagName() { return "STRING"; }

  static boost::shared_ptr<Token> parse(std::fstream &fs);
};

class Tokenizer {
public:
  boost::shared_ptr<Token> next(std::fstream &fs);
};

typedef boost::shared_ptr<Token> (*TokenParsingFunc)(std::fstream &fs);

const TokenParsingFunc TOKEN_PARSING_FUNCS[] ={
  &ParenToken::parse,
  &StringToken::parse
};

const size_t TOKEN_PARSING_FUNCS_LENGTH = sizeof(TOKEN_PARSING_FUNCS) /
  sizeof(TOKEN_PARSING_FUNCS[0]);


#endif
