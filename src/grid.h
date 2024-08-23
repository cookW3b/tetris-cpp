#pragma once
#include "raylib.h"
#include "vec2int.h"

class Grid {
public:
  Grid(int cols, int rows, int cellSize);
  Vec2Int position;
  void render();
  void destroy();

  bool isFilled(int col, int row);
  void fill(int col, int row, Color color);
  void clear(int col, int row);
  void clearRow(int row);
private:
  int cols;
  int rows;
  int cellSize;

  Color *cells;
};