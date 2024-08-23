#include "next_shape_board.h"
#include "raylib.h"

NextShapeBoard::NextShapeBoard(Shape *shape) {
  this->shape = shape;
  this->shape->cellSize = 40;
}

void NextShapeBoard::render() {
  DrawText(
    "Next Shape",
    this->position.x + 18, this->position.y + 20,
    40, WHITE
  );
  DrawRectangleLines(
    this->position.x, this->position.y,
    280, 280,
    WHITE
  );
  this->shape->position.x = this->position.x + 80;
  this->shape->position.y = this->position.y + 140;
  this->shape->update();
  this->shape->render();
}