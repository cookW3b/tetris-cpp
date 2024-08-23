#include "shape.h"
#include <stdlib.h>
#include <cmath>
#include "stdio.h"

Shape::Shape(int cellSize) {
  this->rotation = 0;
  this->cellCount = 4;
  this->cells = (Vec2Int*)malloc(this->cellCount * sizeof(Vec2Int));
  this->rects = (Vec2Int*)malloc(this->cellCount * sizeof(Vec2Int));

  this->cellSize = cellSize;
  this->color = WHITE;

  this->setRandomType();
  this->setRandomColor();

  this->update();
}

void Shape::render() {
  for (int i = 0; i < this->cellCount; i++) {
    DrawRectangle(
      this->rects[i].x, this->rects[i].y,
      cellSize, cellSize, this->color
    );
  }
}

void Shape::setRandomType() {
  this->type = ShapeType(GetRandomValue(0, 4));
}

void Shape::setRandomColor() {
  static constexpr Color possibleColors[5] = {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA
  };
  this->color = possibleColors[GetRandomValue(0, 4)];
}

void Shape::setType(ShapeType type) {
  this->type = type;
}

void Shape::update() {
  this->updateCellPositions();
  this->updateCenterCoords();
  if (this->type != ShapeType::O) {
    this->rotateCells();
  }
  this->updateRectPositions();
}

void Shape::updateCellPositions() {
  switch(this->type) {
    case ShapeType::I:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 1;
      this->cells[1].y = 0;

      this->cells[2].x = 2;
      this->cells[2].y = 0;

      this->cells[3].x = 3;
      this->cells[3].y = 0;
      break;
    case ShapeType::L:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 0;
      this->cells[1].y = 1;

      this->cells[2].x = 0;
      this->cells[2].y = 2;

      this->cells[3].x = 1;
      this->cells[3].y = 2;
      break;
    case ShapeType::J:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 0;
      this->cells[1].y = 1;

      this->cells[2].x = 0;
      this->cells[2].y = 2;

      this->cells[3].x = -1;
      this->cells[3].y = 2;
      break;
    case ShapeType::O:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 0;
      this->cells[1].y = 1;

      this->cells[2].x = 1;
      this->cells[2].y = 0;

      this->cells[3].x = 1;
      this->cells[3].y = 1;
      break;
    case ShapeType::Z:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 1;
      this->cells[1].y = 0;

      this->cells[2].x = 1;
      this->cells[2].y = 1;

      this->cells[3].x = 2;
      this->cells[3].y = 1;
      break;
    case ShapeType::S:
      this->cells[0].x = 0;
      this->cells[0].y = 1;

      this->cells[1].x = 1;
      this->cells[1].y = 1;

      this->cells[2].x = 1;
      this->cells[2].y = 0;

      this->cells[3].x = 2;
      this->cells[3].y = 0;
      break;
    case ShapeType::T:
      this->cells[0].x = 0;
      this->cells[0].y = 0;

      this->cells[1].x = 1;
      this->cells[1].y = 0;

      this->cells[2].x = 2;
      this->cells[2].y = 0;

      this->cells[3].x = 1;
      this->cells[3].y = 1;
      break;
    default:
      break;
  }
}

void Shape::rotateCells() {
  int _sin = sin(this->rotation);
  int _cos = cos(this->rotation);

  for (int i = 0; i < this->cellCount; i++) {
    int cellX = this->cells[i].x - int(this->center.x);
    int cellY = this->cells[i].y - int(this->center.y);

    int rotatedX = (_cos * cellX) - (_sin * cellY);
    int rotatedY = (_sin * cellX) + (_cos * cellY);

    rotatedX += int(this->center.x);
    rotatedY += int(this->center.y);

    this->cells[i].x = rotatedX;
    this->cells[i].y = rotatedY;
  }
}

void Shape::updateCenterCoords() {
  this->center.x = 0;
  this->center.y = 0;
  for (int i = 0; i < this->cellCount; i++) {
    this->center.x += this->cells[i].x;
    this->center.y += this->cells[i].y;
  }
  this->center.x /= this->cellCount;
  this->center.y /= this->cellCount;
}

void Shape::updateRectPositions() {
  for (int i = 0; i < this->cellCount; i++) {
    this->rects[i].x = (this->cells[i].x * cellSize) + this->position.x;
    this->rects[i].y = (this->cells[i].y * cellSize) + this->position.y;
  }
}

void Shape::destroy() {
  free(this->cells);
  free(this->rects);
}