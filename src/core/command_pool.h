#pragma once
#include "commands.h"

class CommandPool {
private:
  Command** history;
  unsigned int count;
  unsigned int capacity;
public:
  CommandPool(unsigned int capacity);
  void execute(Command *command);
  void undo();
  void clear();
  void destroy();
};