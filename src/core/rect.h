#pragma once
#include "raylib.h"

class Rect {
public:
  Rect(int x, int y, int width, int height, Color color);
  Rect();
  Color color;
  Vector2 position;
  int width;
  int height;
  void render();
};