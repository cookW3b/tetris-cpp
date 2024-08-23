#include "raylib.h"
#include "shape.h"
#include "command_pool.h"
#include "controller.h"
#include "commands.h"
#include "grid.h"
#include "next_shape_board.h"
#include <string>

int main() {
  int windowWidth = 1280;
  int windowHeight = 720;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "raylib [core] example - basic window");

  int cellSize = 35;

  Shape currentShape = Shape(cellSize);
  currentShape.position.x = windowWidth  / 2;
  currentShape.position.y = windowHeight / 2;

  int cols = 10;
  int rows = 20;
  Grid grid = Grid(10, 20, cellSize);
  grid.position.x = (windowWidth  / 2) - (cellSize * cols / 2);
  grid.position.y = (windowHeight / 2) - (cellSize * rows / 2);

  Shape nextShape = Shape(cellSize);
  NextShapeBoard nextShapeBoard = NextShapeBoard(&nextShape);
  nextShapeBoard.position.x = (grid.position.x + (cols * cellSize)) + 100;
  nextShapeBoard.position.y = (windowHeight / 2) - 200;

  MoveRight moveRight = MoveRight(&currentShape.position, currentShape.cellSize);
  MoveLeft  moveLeft  = MoveLeft(&currentShape.position, currentShape.cellSize);
  MoveDown  moveDown  = MoveDown(&currentShape.position, currentShape.cellSize);
  Rotate    rotate    = Rotate(&currentShape.rotation, PI / 2);

  CommandPool commandPool = CommandPool(100);
  Controller  controller  = Controller(5);
  controller.setCommandPool(&commandPool);
  controller.bind(KEY_D,     &moveRight);
  controller.bind(KEY_A,     &moveLeft);
  controller.bind(KEY_S,     &moveDown);
  controller.bind(KEY_SPACE, &rotate);

  Camera2D camera {};
  camera.offset = { windowWidth / 2.0f, windowHeight / 2.0f };
  camera.target = {
    static_cast<float>(currentShape.position.x),
    static_cast<float>(currentShape.position.y)
  };
  camera.rotation = 0.0;
  camera.zoom = 1.0;

  bool gameStarted = false;
  int currentScore = 0;
  int lastScore = 0;

  int passedFrames = 0;

  while (!WindowShouldClose()) {
    camera.zoom = GetScreenWidth() / 1300.0f;
    camera.offset.x = GetScreenWidth() / 2.0f;
    camera.offset.y = GetScreenHeight() / 2.0f;

    BeginDrawing();
      BeginMode2D(camera);
        ClearBackground(BLACK);

        if (!gameStarted) {
          DrawText(
            "Press SPACE to start",
            windowWidth / 2 - 280, windowHeight / 2 - 100,
            50, WHITE
          );

          if (lastScore > 0) {
            DrawText(
              ("Last Score: " + std::to_string(lastScore)).c_str(),
              windowWidth / 2 - 200, windowHeight / 2, 50, WHITE
            );
          }

          if (IsKeyPressed(KEY_SPACE)) {
            gameStarted = true;
          }

          EndMode2D();
          EndDrawing();
          continue;
        }

        if (passedFrames % 20 == 0) {
          currentShape.position.y += cellSize;
          passedFrames = 0;
        }

        controller.process();

        DrawText(
          ("Score: " + std::to_string(currentScore)).c_str(),
          nextShapeBoard.position.x, nextShapeBoard.position.y - 100,
          50, WHITE
        );

        currentShape.update();

        bool isCollided = false;

        for (int i = 0; i < currentShape.cellCount; i++) {
          int col = (currentShape.rects[i].x - grid.position.x) / cellSize;
          int row = (currentShape.rects[i].y - grid.position.y) / cellSize;

          while (
            currentShape.rects[i].x < grid.position.x
            || currentShape.rects[i].x >= grid.position.x + (cols * cellSize)
            || currentShape.rects[i].y >= grid.position.y + (rows * cellSize)
            || grid.isFilled(col, row)
          ) {
            commandPool.undo();
            currentShape.update();
            col = (currentShape.rects[i].x - grid.position.x) / cellSize;
            row = (currentShape.rects[i].y - grid.position.y) / cellSize;
          }

          if (grid.isFilled(col, row + 1) || row == rows - 1) {
            isCollided = true;
          }
        }

        if (isCollided) {
          for (int i = 0; i < currentShape.cellCount; i++) {
            int col = (currentShape.rects[i].x - grid.position.x) / cellSize;
            int row = (currentShape.rects[i].y - grid.position.y) / cellSize;

            grid.fill(col, row, currentShape.color);

            if (row < 0) {
              gameStarted = false;
              lastScore = currentScore;
              currentScore = 0;
              commandPool.clear();
              break;
            }
          }

          currentShape.type = nextShape.type;
          currentShape.color = nextShape.color;
          currentShape.position.x = windowWidth / 2;
          currentShape.position.y = grid.position.y;
          currentShape.rotation = 0;
          nextShape.setRandomType();
          nextShape.setRandomColor();
        }

        for (int row = 0; row < rows; row++) {
          int filledCount = 0;
          for (int col = 0; col < cols; col++) {
            if (grid.isFilled(col, row)) {
              filledCount++;
            }
          }

          if (filledCount == cols) {
            grid.clearRow(row);
            currentScore += 100;
          }
        }

        currentShape.render();
        grid.render();
        nextShapeBoard.render();

      EndMode2D();
    EndDrawing();
    passedFrames++;
  }

  currentShape.destroy();
  commandPool.destroy();
  grid.destroy();
  CloseWindow();

  return 0;
}