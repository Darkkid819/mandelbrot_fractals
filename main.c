#include "raylib.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Mandelbrot Set");

    Shader shader = LoadShader(0, "mandelbrot.fs");
    int centerLoc = GetShaderLocation(shader, "center");
    int scaleLoc = GetShaderLocation(shader, "scale");
    int aspectRatioLoc = GetShaderLocation(shader, "aspectRatio");
    int maxIterationsLoc = GetShaderLocation(shader, "maxIterations");

    Vector2 center = {0.0f, 0.0f};
    float scale = 0.01f;
    float aspectRatio = (float)screenHeight / (float)screenWidth;
    int maxIterations = 1000;

    SetShaderValue(shader, scaleLoc, &scale, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, aspectRatioLoc, &aspectRatio, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, maxIterationsLoc, &maxIterations, SHADER_UNIFORM_INT);

    SetTargetFPS(60);

    while (!WindowShouldClose()) { 

        if (IsKeyDown(KEY_RIGHT)) center.x += 2.0f * scale;
        if (IsKeyDown(KEY_LEFT)) center.x -= 2.0f * scale;
        if (IsKeyDown(KEY_UP)) center.y += 2.0f * scale;
        if (IsKeyDown(KEY_DOWN)) center.y -= 2.0f * scale;

        float wheelMove = GetMouseWheelMove();
        scale *= (1.0f - wheelMove * 0.1f);

        SetShaderValue(shader, centerLoc, &center, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, scaleLoc, &scale, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
