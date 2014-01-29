#ifndef _TOKEN_H_
#define _TOKEN_H_

#define REJECT_STATE 99999

class Token {
public:
  Token(std::string value) : value(value) {}

  std::string getText() { return value; }

  virtual std::string getTagName() = 0;

private:
  std::string value;
};

#endif

