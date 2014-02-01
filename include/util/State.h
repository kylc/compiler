#ifndef _STATE_H_
#define _STATE_H_

class State {
public:
  State(int id, bool endState) : id(id), endState(endState) {}

  int getId() { return id; }
  bool isEndState() { return endState; }

private:
  int id;
  bool endState;
};


#endif
