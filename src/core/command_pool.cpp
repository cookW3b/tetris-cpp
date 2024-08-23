#include "command_pool.h"
#include <stdlib.h>

CommandPool::CommandPool(unsigned int capacity) {
  this->count = 0;
  this->capacity = capacity;
  this->history = (Command**)malloc(this->capacity * sizeof(Command*));
}

void CommandPool::execute(Command *command) {
  command->execute();
  this->history[this->count] = command;
  this->count++;
  if (this->count >= this->capacity) {
    this->count = 0;
  }
}

void CommandPool::clear() {
  this->count = 0;
}

void CommandPool::undo() {
  if (this->count == 0) return;

  this->history[this->count - 1]->undo();
  this->count--;
}

void CommandPool::destroy() {
  free(this->history);
}