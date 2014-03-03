#include <iostream>
#include <string>

void info(std::string msg) {
  std::cout << "[info] " << msg << std::endl;
}

void warn(std::string msg) {
  std::cout << "[warn] " << msg << std::endl;
}

void fail(std::string msg) {
  std::cout << "[fail] " << msg << std::endl;
  exit(0);
}
