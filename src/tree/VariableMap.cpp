#include "tree/VariableMap.h"

#include <boost/scoped_ptr.hpp>

VariableMap::VariableMap() {
}

bool VariableMap::contains(std::string key) {
  if(table.count(key)) {
    return true;
  } else {
    if(parent) {
      return parent->contains(key);
    } else {
      return false;
    }
  }
}

Variable *VariableMap::lookup(std::string key) {
  if(table.count(key)) {
    return table.at(key);
  } else {
    if(parent) {
      return parent->lookup(key);
    } else {
      throw std::runtime_error("Variable '" + key + "' does not exist");
    }
  }
}

void VariableMap::insert(std::string key, Variable *value) {
  if(contains(key)) {
    throw std::runtime_error("Variable '" + key + "' already exists");
  }

  table[key] = value;
}

void VariableMap::insertToParent(std::string key, Variable *value) {
  parent->insert(key, value);
}

void VariableMap::setParent(boost::shared_ptr<VariableMap> p) {
  parent = p;
}

Variable::Variable(Type type) : type(type) {
}

Type Variable::getType() {
  return type;
}
