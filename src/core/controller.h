#pragma once
#include "raylib.h"
#include "commands.h"
#include "command_pool.h"
#include <map>

class Controller {
private:
  CommandPool *commandPool = nullptr;
  std::map<KeyboardKey, Command *> keyMap;
  unsigned int repeatDelay = 0;
  unsigned int elapsedTime = 0;
public:
  Controller(unsigned int repeatDelay);
  void process();
  void bind(KeyboardKey key, Command *command);
  void setCommandPool(CommandPool *commandPool);
};