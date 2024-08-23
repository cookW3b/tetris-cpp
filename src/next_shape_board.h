#pragma once
#include "shape.h"

class NextShapeBoard {
public:
  Vector2 position;
  Shape* shape;
  NextShapeBoard(Shape* shape);
  void render();
};