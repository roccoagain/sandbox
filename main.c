#include <stdlib.h>

#include "raylib.h"

#define MAX_PIXELS 20000

typedef struct Pixel {
  Vector2 position;
  float velocity;
  bool isFalling;
} Pixel;

int main(void) {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Sandbox");

  // Define gravity and pixel properties
  Pixel pixels[MAX_PIXELS];
  int pixelsCount = 0;
  float gravity = 5.0f;
  float deltaTime = 0.0f;
  int ground[screenWidth];  // Array representing the current 'ground' level for
                            // each x position

  // Initialize ground level
  for (int i = 0; i < screenWidth; i++) {
    ground[i] = screenHeight;
  }

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    deltaTime = GetFrameTime();

    // Spawn pixels with a random offset
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && pixelsCount < MAX_PIXELS) {
      for (int i = 0; i < 10; i++) {   // Increase spawn rate
        int randX = rand() % 21 - 10;  // Random offset between -10 and 10
        int randY = rand() % 21 - 10;

        int spawnX = GetMouseX() + randX;
        if (spawnX >= 0 &&
            spawnX < screenWidth) {  // Ensure spawn is within screen bounds
          pixels[pixelsCount] =
              (Pixel){.position = (Vector2){spawnX, GetMouseY() + randY},
                      .velocity = 0.0f,
                      .isFalling = true};
          pixelsCount++;
          if (pixelsCount >= MAX_PIXELS) {
            break;
          }
        }
      }
    }

    // Update each pixel's position
    for (int i = 0; i < pixelsCount; i++) {
      if (pixels[i].isFalling) {
        // Apply gravity and update position
        pixels[i].velocity += gravity * deltaTime;
        pixels[i].position.y += pixels[i].velocity;

        // Collision detection with the ground
        int px = (int)pixels[i].position.x;
        if (px >= 0 && px < screenWidth) {  // Check if within screen bounds
          if (pixels[i].position.y >= ground[px] - 1) {
            pixels[i].position.y = ground[px] - 1;
            pixels[i].isFalling = false;
            ground[px]--;  // Raise the ground level at this x position
          }
        }
      }
    }

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int i = 0; i < pixelsCount; i++) {
      DrawPixelV(pixels[i].position, BLACK);
    }

    DrawText("Hold the left mouse button to spawn pixels.", 10, 10, 20,
             DARKGRAY);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}
