#pragma once
#include "rect.h"
#include "vec2int.h"

enum ShapeType : char {
  T, L, I, J, O, S, Z
};

class Shape {
private:
  void updateCellPositions();
  void updateRectPositions();
  void updateCenterCoords();
  void rotateCells();

  Vec2Int *cells;

  Vec2Int center;

public:
  void update();

  Shape(int cellSize);

  Vec2Int *rects;

  size_t   cellCount;

  ShapeType type;
  Color     color;

  float   rotation;
  Vec2Int position;

  int cellSize;

  void render();
  void setRandomType();
  void setRandomColor();
  void setType(ShapeType type);
  void destroy();
};