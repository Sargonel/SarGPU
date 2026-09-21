#include "examples.h"

static Font demoFont;

void TextDemoInit(void) {
    SetWindowTitle("SarGPU Examples - Text & Fonts");
    demoFont = LoadFontEx("examples/assets/font.ttf", 64, 0, 0);
}
void TextDemoShutdown(void) {
    if (IsFontValid(demoFont)) UnloadFont(demoFont);
    demoFont = (Font){0};
}

static void DemoText(const char *text, Vector2 position, float size, float spacing, Color color) {
    if (IsFontValid(demoFont))
        DrawTextEx(demoFont, text, position, size, spacing, color);
    else
        DrawText(text, (int)position.x, (int)position.y, (int)size, color);
}

void TextDemoUpdate(void) {
    float t = (float)GetTime();
    int pulse = 48 + (int)(Sin(t * 2.0f) * 7.0f);
    BeginDrawing();
    ClearBackground((Color){12, 9, 25, 255});
    DrawRectangleGradientV(0, 0, 1920, 1080, (Color){48, 24, 75, 255}, (Color){9, 8, 20, 255});
    DrawText("TEXT & FONTS", 70, 50, 48, RAYWHITE);
    DrawText("Custom TTF when available, built-in fallback everywhere", 72, 112, 22, LIGHTGRAY);
    DemoText("Typography should feel alive.", (Vector2){110, 230}, 64, 2, (Color){230, 210, 255, 255});
    DemoText("SarGPU keeps the same C source on native and web.", (Vector2){112, 330}, 34, 1, (Color){150, 205, 255, 255});
    DrawRectangleRounded((Rectangle){110, 455, 1050, 330}, .08f, 12, (Color){10, 12, 28, 190});
    DrawRectangleRoundedLinesEx((Rectangle){110, 455, 1050, 330}, .08f, 12, 2, (Color){100, 75, 145, 255});
    DrawText(TextFormat("Time %.2f s / FPS %d", GetTime(), GetFPS()), 150, 500, 29, RAYWHITE);
    DrawText(TextFormat("Step %.2f ms", GetFrameTime() * 1000.0f), 150, 548, 25, LIGHTGRAY);
    DrawText(TextFormat("Padding %04d / Hex 0x%04X / 100%%", 42, 48879), 150, 600, 26, (Color){180, 230, 255, 255});
    DrawText(TextToUpper("case conversion with TextToUpper"), 150, 655, 24, (Color){255, 175, 210, 255});
    DrawText("TextSubtext result:", 150, 705, 20, GRAY);
    DrawText(TextSubtext("SELECTED PART | HIDDEN ENDING", 0, 13), 520, 701, 25, (Color){175, 255, 205, 255});
    DrawRectangleRounded((Rectangle){1210, 455, 600, 330}, .08f, 12, (Color){10, 12, 28, 190});
    DrawRectangleRoundedLinesEx((Rectangle){1210, 455, 600, 330}, .08f, 12, 2, (Color){100, 75, 145, 255});
    DrawText("DRAWTEXTPRO", 1390, 500, 23, GRAY);
    {
        Font rotatingFont = IsFontValid(demoFont) ? demoFont : GetFontDefault();
        const char *spin = "ROTATING";
        Vector2 textSize = MeasureTextEx(rotatingFont, spin, 52, 2);
        DrawTextPro(rotatingFont, spin, (Vector2){1510, 650}, (Vector2){textSize.x / 2, textSize.y / 2}, Sin(t * 1.7f) * 28.0f, 52, 2, GOLD);
    }
    DrawText("SIZE", 150, 840, 20, GRAY);
    DrawText(TextFormat("%d PX", pulse), 150, 875, pulse, (Color){205, 150, 255, 255});
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
