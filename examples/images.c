#include "examples.h"

static Texture2D imageTextures[4];

static void DrawImageTextFitted(const char *text, int x, int y, int preferredSize, int maxWidth, Color color) {
    int size = preferredSize;
    while (size > 12 && MeasureText(text, size) > maxWidth) size--;
    DrawText(text, x, y, size, color);
}

void ImagesInit(void) {
    SetWindowTitle("SarGPU Examples - Image Lab");
    Image source = GenImagePerlinNoise(320, 240, 8, 16, 7.0f);
    Image gradient = GenImageGradientRadial(320, 240, .25f, (Color){255, 210, 80, 255}, (Color){55, 25, 115, 255});
    Image inverted = ImageCopy(source);
    ImageColorInvert(&inverted);
    Image tinted = ImageCopy(source);
    ImageColorTint(&tinted, (Color){90, 220, 255, 255});
    ImageBlurGaussian(&tinted, 5);
    imageTextures[0] = LoadTextureFromImage(source);
    imageTextures[1] = LoadTextureFromImage(gradient);
    imageTextures[2] = LoadTextureFromImage(inverted);
    imageTextures[3] = LoadTextureFromImage(tinted);
    for (int i = 0; i < 4; i++) {
        GenTextureMipmaps(&imageTextures[i]);
        SetTextureFilter(imageTextures[i], TEXTURE_FILTER_TRILINEAR);
    }
    UnloadImage(source);
    UnloadImage(gradient);
    UnloadImage(inverted);
    UnloadImage(tinted);
}

void ImagesShutdown(void) {
    for (int i = 0; i < 4; i++) {
        if (IsTextureValid(imageTextures[i])) UnloadTexture(imageTextures[i]);
        imageTextures[i] = (Texture2D){0};
    }
}

void ImagesUpdate(void) {
    const char *labels[4] = {"PERLIN NOISE", "RADIAL GRADIENT", "COLOR INVERT", "TINT + BLUR"};
    const char *details[4] = {"Generated procedural noise", "Generated radial color field", "Copied then inverted on CPU", "Tinted then Gaussian blurred"};
    BeginDrawing();
    ClearBackground((Color){8, 12, 20, 255});
    DrawRectangleGradientV(0, 0, 1920, 1080, (Color){35, 27, 52, 255}, (Color){5, 8, 14, 255});
    DrawText("IMAGE LAB", 70, 50, 48, RAYWHITE);
    DrawText("Images are generated and processed on the CPU, then uploaded as mipmapped textures", 72, 112, 21, LIGHTGRAY);
    for (int i = 0; i < 4; i++) {
        int x = 70 + (i % 2) * 920, y = 200 + (i / 2) * 390;
        Color accent = i == 1 ? GOLD : (Color){130, 210, 255, 255};
        DrawRectangleRounded((Rectangle){x, y, 860, 340}, .06f, 12, (Color){14, 21, 35, 245});
        DrawRectangleRoundedLinesEx((Rectangle){x, y, 860, 340}, .06f, 12, 2, (Color){55, 75, 105, 255});
        DrawTexturePro(imageTextures[i], (Rectangle){0, 0, 320, 240}, (Rectangle){x + 20, y + 20, 400, 300}, (Vector2){0}, 0, WHITE);
        DrawImageTextFitted(labels[i], x + 455, y + 55, 25, 375, accent);
        DrawImageTextFitted(details[i], x + 455, y + 112, 18, 375, LIGHTGRAY);
        DrawImageTextFitted(TextFormat("SIZE  %d X %d", imageTextures[i].width, imageTextures[i].height), x + 455, y + 180, 18, 375, GRAY);
        DrawImageTextFitted(TextFormat("MIP LEVELS  %d", imageTextures[i].mipmaps), x + 455, y + 220, 18, 375, GRAY);
        DrawImageTextFitted("TRILINEAR FILTER", x + 455, y + 260, 18, 375, GRAY);
    }
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
