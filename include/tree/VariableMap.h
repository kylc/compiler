#ifndef _VARIABLE_MAP_H_
#define _VARIABLE_MAP_H_

#include <unordered_map>
#include <boost/shared_ptr.hpp>

#include "tree/Type.h"

class Variable {
public:
  Variable(Type type);

  Type getType();

private:
  Type type;
};

class VariableMap {
public:
  VariableMap();
  bool contains(std::string key);
  Variable *lookup(std::string key);
  void insert(std::string key, Variable *value);
  void insertToParent(std::string key, Variable *value);

  void setParent(boost::shared_ptr<VariableMap> p);
private:
  boost::shared_ptr<VariableMap> parent;
  std::unordered_map<std::string, Variable *> table;
};

#endif
