#include "raylib.h"

int mandelbrot(float x, float y, int maxIterations) {
    float zx = 0.0, zy = 0.0, zx2 = 0.0, zy2 = 0.0;
    int iterations = 0;
    while (zx2 + zy2 < 4.0 && iterations < maxIterations) {
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

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    float scale = 4.0;
    Vector2 center = {0.0, 0.0};

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) center.x += 0.02 * scale;
        if (IsKeyDown(KEY_LEFT)) center.x -= 0.02 * scale;
        if (IsKeyDown(KEY_UP)) center.y -= 0.02 * scale;
        if (IsKeyDown(KEY_DOWN)) center.y += 0.02 * scale;

        float wheelMove = GetMouseWheelMove();
        scale *= (1 - wheelMove * 0.1);

        BeginTextureMode(target);
            ClearBackground(BLANK);
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    float scaledX = (x - screenWidth / 2.0) * scale / screenWidth + center.x;
                    float scaledY = (y - screenHeight / 2.0) * scale / screenHeight + center.y;
                    int color = mandelbrot(scaledX, scaledY, 1000);
                    DrawPixel(x, y, ColorFromHSV(color % 256, 1.0, color < 1000 ? 1.0 : 0));
                }  
            }
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(target.texture, (Rectangle){ 0, 0, target.texture.width, -target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
