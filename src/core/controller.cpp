#include "controller.h"

Controller::Controller(unsigned int repeatDelay) {
  this->repeatDelay = repeatDelay;
  this->elapsedTime = 0;
}

void Controller::bind(KeyboardKey key, Command *command) {
  this->keyMap[key] = command;
}

void Controller::setCommandPool(CommandPool *commandPool) {
  this->commandPool = commandPool;
}

void Controller::process() {
  this->elapsedTime++;
  if (this->elapsedTime < this->repeatDelay) return;
  this->elapsedTime = 0;
  for (auto const& [key, command] : this->keyMap) {
    if (IsKeyDown(key)) {
      if (this->commandPool == nullptr) {
        command->execute();
      } else {
        this->commandPool->execute(command);
      }
      break;
    }
  }
}