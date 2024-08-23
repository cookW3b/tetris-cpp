#include "grid.h"
#include <stdlib.h>

Grid::Grid(int cols, int rows, int cellSize) {
  this->cols = cols;
  this->rows = rows;
  this->cellSize = cellSize;
  this->position.x = 0;
  this->position.y = 0;

  this->cells = (Color*)malloc(sizeof(Color) * (cols * rows));

  for (int i = 0; i < cols * rows; i++) {
    this->cells[i] = WHITE;
    this->cells[i].a = 0;
  }
}

void Grid::render() {
  for (int c = 0; c < this->cols; c++) {
    for (int r = 0; r < this->rows; r++) {
      Color cellColor = this->cells[(r * this->cols + c)];
      if (cellColor.a == 0) {
        continue;
      }
      DrawRectangle(
        this->position.x + (c * this->cellSize),
        this->position.y + (r * this->cellSize),
        this->cellSize, this->cellSize,
        cellColor
      );
    }
  }

  for (int i = 0; i <= this->cols; i++) {
    DrawLine(
      this->position.x + (i * this->cellSize),
      this->position.y,
      this->position.x + (i * this->cellSize),
      this->position.y + (this->rows * this->cellSize),
      WHITE
    );
  }

  for (int i = 0; i <= this->rows; i++) {
    DrawLine(
      this->position.x,
      this->position.y + (i * this->cellSize),
      this->position.x + (this->cols * this->cellSize),
      this->position.y + (i * this->cellSize),
      WHITE
    );
  }
}

bool Grid::isFilled(int col, int row) {
  return this->cells[(row * this->cols) + col].a > 0;
}

void Grid::fill(int col, int row, Color color) {
  this->cells[(row * this->cols) + col] = color;
}

void Grid::clear(int col, int row) {
  this->cells[(row * this->cols) + col].a = 0;
}

void Grid::clearRow(int row) {
  for (int c = 0; c < this->cols; c++) {
    this->cells[(row * this->cols) + c].a = 0;

    for (int r = row; r > 0; r--) {
      if (this->isFilled(c, r - 1)) {
        this->cells[(r * this->cols) + c] = this->cells[((r - 1) * this->cols) + c];
        this->clear(c, r - 1);
      }
    }
  }
}

void Grid::destroy() {
  free(this->cells);
}