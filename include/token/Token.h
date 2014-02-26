#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <unordered_map>

#define REJECT_STATE 99999

class Token {
public:
  Token(std::string value) : value(value) {}

  std::string getText() { return value; }

  virtual unsigned int getType() = 0;
  virtual std::string getTagName() = 0;

private:
  std::string value;
};

typedef std::unordered_map<std::string, boost::shared_ptr<Token>> SymbolTable;
typedef boost::shared_ptr<SymbolTable> SymbolTablePtr;

#endif

