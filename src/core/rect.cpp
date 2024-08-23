#include "rect.h"
#include <stdio.h>

Rect::Rect() {
  this->position.x = 0;
  this->position.y = 0;
  this->width = 0;
  this->height = 0;
  this->color = WHITE;
}

Rect::Rect(int x, int y, int width, int height, Color color) {
  this->position.x = x;
  this->position.y = y;
  this->width = width;
  this->height = height;
  this->color = color;
}

void Rect::render() {
  DrawRectangle(
    this->position.x,
    this->position.y,
    this->width,
    this->height,
    this->color
  );
}