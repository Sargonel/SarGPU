#include "examples.h"

static Camera2D demoCamera;

void CameraDemoInit(void) {
    SetWindowTitle("SarGPU Examples - 2D Camera");
    demoCamera = (Camera2D){{960, 540}, {0, 0}, 0, 1};
}
void CameraDemoShutdown(void) {}

void CameraDemoUpdate(void) {
    float speed = 650.0f * GetFrameTime() / demoCamera.zoom;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) demoCamera.target.x -= speed;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) demoCamera.target.x += speed;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) demoCamera.target.y -= speed;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) demoCamera.target.y += speed;

    float wheel = GetMouseWheelMove();

    if (wheel != 0) {
        Vector2 mouse = GetMousePosition(), before = GetScreenToWorld2D(mouse, demoCamera);

        demoCamera.zoom += wheel * .12f * demoCamera.zoom;
        if (demoCamera.zoom < .25f) demoCamera.zoom = .25f;
        if (demoCamera.zoom > 4) demoCamera.zoom = 4;

        Vector2 after = GetScreenToWorld2D(mouse, demoCamera);
        demoCamera.target.x += before.x - after.x;
        demoCamera.target.y += before.y - after.y;
    }
    if (IsKeyPressed(KEY_R)) demoCamera = (Camera2D){{960, 540}, {0, 0}, 0, 1};

    Vector2 worldMouse = GetScreenToWorld2D(GetMousePosition(), demoCamera);

    BeginDrawing();
    ClearBackground((Color){7, 12, 20, 255});
    BeginMode2D(demoCamera);
    for (int x = -2400; x <= 2400; x += 100)
        DrawLineEx((Vector2){x, -1800}, (Vector2){x, 1800}, (x == 0 ? 2.0f : 1.0f) / demoCamera.zoom, x == 0 ? RED : (Color){35, 52, 68, 255});
    for (int y = -1800; y <= 1800; y += 100)
        DrawLineEx((Vector2){-2400, y}, (Vector2){2400, y}, (y == 0 ? 2.0f : 1.0f) / demoCamera.zoom, y == 0 ? GREEN : (Color){35, 52, 68, 255});
    for (int i = 0; i < 24; i++) {
        float x = (i % 6 - 3) * 360.0f, y = (i / 6 - 2) * 330.0f;
        Color c = ColorFromHSV((float)i * 15, 0.65f, 0.9f);
        DrawPoly((Vector2){x, y}, 3 + i % 6, 65, i * 12, c);
        DrawText(TextFormat("%d", i + 1), (int)x - 8, (int)y - 12, 20, BLACK);
    }
    DrawCircleV(worldMouse, 18.0f / demoCamera.zoom, (Color){255, 220, 90, 220});
    EndMode2D();
    DrawRectangleRounded((Rectangle){32, 32, 600, 145}, .12f, 10, (Color){7, 12, 24, 220});
    DrawText("2D CAMERA", 55, 50, 38, RAYWHITE);
    DrawText("WASD / arrows pan / wheel zooms at pointer / R reset", 56, 98, 20, LIGHTGRAY);
    DrawText(TextFormat("World mouse %.0f, %.0f   Zoom %.2fx", worldMouse.x, worldMouse.y, demoCamera.zoom), 56, 133, 19, GOLD);
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
