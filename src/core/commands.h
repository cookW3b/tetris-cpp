#pragma once
#include "raylib.h"
#include "vec2int.h"

class Command {
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
};

class MoveDown : public Command {
private:
  Vec2Int *position;
public:
  MoveDown(Vec2Int *position, int velocity);
  int velocity;
  void execute() override;
  void undo() override;
};

class MoveLeft : public Command {
private:
  Vec2Int *position;
public:
  MoveLeft(Vec2Int *position, int velocity);
  int velocity;
  void execute() override;
  void undo() override;
};

class MoveRight : public Command {
private:
  Vec2Int *position;
public:
  MoveRight(Vec2Int *position, int velocity);
  int velocity;
  void execute() override;
  void undo() override;
};

class Rotate : public Command {
private:
  float *rotation;
public:
  Rotate(float *rotation, float angle);
  float angle;
  void execute() override;
  void undo() override;
};