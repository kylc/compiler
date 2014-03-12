#ifndef _VARIABLE_MAP_H_
#define _VARIABLE_MAP_H_

#include <unordered_map>

class VariableMap {
public:
  VariableMap(VariableMap parent);
private:
  unordered_map table;
};

#endif
