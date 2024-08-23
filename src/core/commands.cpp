#include "commands.h"

MoveDown::MoveDown(Vec2Int *position, int velocity) {
  this->position = position;
  this->velocity = velocity;
}

void MoveDown::execute() {
  this->position->y += this->velocity;
}

void MoveDown::undo() {
  this->position->y -= this->velocity;
}

MoveLeft::MoveLeft(Vec2Int *position, int velocity) {
  this->position = position;
  this->velocity = velocity;
}

void MoveLeft::execute() {
  this->position->x -= this->velocity;
}

void MoveLeft::undo() {
  this->position->x += this->velocity;
}

MoveRight::MoveRight(Vec2Int *position, int velocity) {
  this->position = position;
  this->velocity = velocity;
}

void MoveRight::execute() {
  this->position->x += this->velocity;
}

void MoveRight::undo() {
  this->position->x -= this->velocity;
}

Rotate::Rotate(float *rotation, float angle) {
  this->rotation = rotation;
  this->angle = angle;
}

void Rotate::execute() {
  *this->rotation += this->angle;
}

void Rotate::undo() {
  *this->rotation -= this->angle;
}