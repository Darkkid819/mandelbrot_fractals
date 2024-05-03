#include "raylib.h"

int mandelbrot(float x, float y, int max_iterations) {
    float zx = 0.0, zy = 0.0, zx2 = 0.0, zy2 = 0.0;
    int iterations = 0;

    while (zx2 + zy2 < 4.0 && iterations < max_iterations) {
        zy = 2.0 * zx * zy + y;
        zx = zx2 - zy2 + x;
        zx2 = zx * zx;
        zy2 = zy * zy;
        iterations++;
    }

    return iterations;
}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Mandelbrot Set");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                float scaledX = (x - screenWidth / 2.0) * 4.0 / screenWidth;
                float scaledY = (y - screenHeight / 2.0) * 4.0 / screenHeight;
                int color = mandelbrot(scaledX, scaledY, 1000);

                DrawPixel(x, y, ColorFromHSV(color % 256, 1.0, color < 1000 ? 1.0 : 0));
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
