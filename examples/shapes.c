#include "examples.h"

void ShapesInit(void) {
    SetWindowTitle("SarGPU Examples - Shapes Lab");
}
void ShapesShutdown(void) {}

void ShapesUpdate(void) {
    float t = (float)GetTime();
    Vector2 mouse = GetMousePosition();
    Vector2 spline[6] = {{120, 770}, {390, 560}, {650, 850}, {930, 600}, {1260, 820}, {1540, 610}};
    float sectorStart = t * 25.0f;
    float sectorSweep = 180.0f + Sin(t * 1.4f) * 135.0f;
    BeginDrawing();
    ClearBackground((Color){8, 12, 24, 255});
    DrawRectangleGradientV(0, 0, 1920, 1080, (Color){20, 28, 54, 255}, (Color){5, 8, 17, 255});
    DrawText("SHAPES LAB", 70, 50, 48, RAYWHITE);
    DrawText("Animated primitives, outlines, splines, blending and scissor", 72, 112, 22, LIGHTGRAY);
    DrawCircleGradient(250, 330, 120, (Color){255, 120, 160, 255}, (Color){80, 20, 80, 0});
    DrawRing((Vector2){250, 330}, 82, 116, t * 35.0f, t * 35.0f + 285.0f, 48, (Color){255, 220, 100, 230});
    DrawRectangleGradientEx((Rectangle){450, 220, 300, 220}, RED, BLUE, GOLD, PURPLE);
    DrawRectangleRoundedLinesEx((Rectangle){450, 220, 300, 220}, .2f, 16, 5, RAYWHITE);
    DrawPoly((Vector2){930, 330}, 6, 120, t * 30.0f, (Color){100, 210, 255, 220});
    DrawPolyLinesEx((Vector2){930, 330}, 6, 120, t * 30.0f, 6, WHITE);
    DrawCircleSector((Vector2){1230, 330}, 120, sectorStart, sectorStart + sectorSweep, 40, (Color){100, 255, 170, 220});
    DrawCircleSectorLines((Vector2){1230, 330}, 120, sectorStart, sectorStart + sectorSweep, 40, WHITE);
    DrawRectanglePro((Rectangle){1515, 330, 210, 110}, (Vector2){105, 55}, t * 32.0f, (Color){255, 120, 85, 230});
    BeginBlendMode(BLEND_ADDITIVE);
    for (int i = 0; i < 8; i++) DrawCircle(1530 + i * 30, 520 + (int)(Sin(t * 3 + i) * 35), 48, (Color){40 + i * 20, 100, 255 - i * 20, 80});
    EndBlendMode();
    DrawSplineCatmullRom(spline, 6, 9, (Color){90, 255, 190, 255});
    for (int i = 0; i < 6; i++) DrawCircleV(spline[i], 10, GOLD);
    BeginScissorMode(1380, 720, 410, 190);
    DrawRectangle(1380, 720, 410, 190, (Color){16, 26, 45, 255});
    DrawCircle((int)mouse.x, (int)mouse.y, 125, (Color){255, 80, 130, 220});
    DrawText("SCISSOR", 1495, 792, 28, RAYWHITE);
    EndScissorMode();
    DrawRectangleLinesEx((Rectangle){1380, 720, 410, 190}, 3, (Color){90, 130, 180, 255});
    DrawText(TextFormat("Mouse: %.0f, %.0f", mouse.x, mouse.y), 72, 1000, 20, GRAY);
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
