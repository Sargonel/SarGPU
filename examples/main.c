#include "examples.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef enum ExampleScreen {
    EXAMPLE_CATALOG,
    EXAMPLE_SNAKE,
    EXAMPLE_BASIC_3D,
    EXAMPLE_SHAPES,
    EXAMPLE_TEXT,
    EXAMPLE_IMAGES,
    EXAMPLE_RENDER_FX,
    EXAMPLE_CAMERA_2D,
    EXAMPLE_AUDIO,
    EXAMPLE_PARTICLES,
    EXAMPLE_LIGHTING_3D
} ExampleScreen;

typedef struct ExampleCard {
    ExampleScreen screen;
    int key;
    const char *title, *description, *features;
    Color accent;
} ExampleCard;

static ExampleScreen currentScreen;
static Rectangle backButton = {1660, 16, 220, 48};
static const ExampleCard cards[] = {
    {EXAMPLE_SNAKE, KEY_ONE, "SNAKE", "Complete 2D mini-game", "Input, sound, shader, render texture", {76, 255, 174, 255}},
    {EXAMPLE_BASIC_3D, KEY_TWO, "BASIC 3D", "Interactive 3D scene", "Models, primitives, depth, picking", {102, 191, 255, 255}},
    {EXAMPLE_SHAPES, KEY_THREE, "SHAPES LAB", "Animated vector showcase", "Shapes, splines, blend and scissor", {255, 113, 145, 255}},
    {EXAMPLE_TEXT, KEY_FOUR, "TEXT & FONTS", "Typography playground", "Fonts, UTF-8, rotation, TextFormat", {205, 150, 255, 255}},
    {EXAMPLE_IMAGES, KEY_FIVE, "IMAGE LAB", "Generated texture gallery", "Noise, gradients, processing, mipmaps", {255, 190, 85, 255}},
    {EXAMPLE_RENDER_FX, KEY_SIX, "RENDER FX", "Offscreen post-processing", "Render textures, WGSL shader, uniforms", {83, 226, 255, 255}},
    {EXAMPLE_CAMERA_2D, KEY_SEVEN, "2D CAMERA", "Explore a large world", "Pan, zoom, transforms, coordinates", {123, 235, 125, 255}},
    {EXAMPLE_AUDIO, KEY_EIGHT, "AUDIO LAB", "Procedural sound board", "Wave generation, pitch, pan, volume", {255, 125, 75, 255}},
    {EXAMPLE_PARTICLES, KEY_NINE, "PARTICLES", "Interactive particle sandbox", "Collisions, additive blend, input", {255, 225, 90, 255}},
    {EXAMPLE_LIGHTING_3D, KEY_ZERO, "LIGHTING 3D", "Advanced generated scene", "Lights, fog, PBR, generated meshes", {125, 160, 255, 255}}};

static bool Clicked(Rectangle bounds) {
    return CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
static int FitTextSize(const char *text, int preferred, int maxWidth) {
    while (preferred > 12 && MeasureText(text, preferred) > maxWidth) preferred--;
    return preferred;
}
static void DrawFittedText(const char *text, int x, int y, int size, int width, Color color) {
    DrawText(text, x, y, FitTextSize(text, size, width), color);
}

void DrawExampleBackButton(void) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), backButton);
    DrawRectangleRounded(backButton, .28f, 8, hover ? (Color){54, 78, 112, 245} : (Color){25, 38, 60, 230});
    DrawRectangleRoundedLinesEx(backButton, .28f, 8, 2, hover ? SKYBLUE : (Color){80, 110, 145, 255});
    const char *label = "<  EXAMPLES";
    int size = FitTextSize(label, 22, (int)backButton.width - 32), width = MeasureText(label, size);
    DrawText(label, (int)(backButton.x + (backButton.width - width) / 2), (int)(backButton.y + (backButton.height - size) / 2), size, RAYWHITE);
}

static void OpenExample(ExampleScreen screen) {
    currentScreen = screen;
    switch (screen) {
    case EXAMPLE_SNAKE:
        SnakeInit();
        break;
    case EXAMPLE_BASIC_3D:
        Basic3DInit();
        break;
    case EXAMPLE_SHAPES:
        ShapesInit();
        break;
    case EXAMPLE_TEXT:
        TextDemoInit();
        break;
    case EXAMPLE_IMAGES:
        ImagesInit();
        break;
    case EXAMPLE_RENDER_FX:
        RenderFxInit();
        break;
    case EXAMPLE_CAMERA_2D:
        CameraDemoInit();
        break;
    case EXAMPLE_AUDIO:
        AudioDemoInit();
        break;
    case EXAMPLE_PARTICLES:
        ParticlesInit();
        break;
    case EXAMPLE_LIGHTING_3D:
        Lighting3DInit();
        break;
    default:
        break;
    }
}

static void CloseExample(void) {
    switch (currentScreen) {
    case EXAMPLE_SNAKE:
        SnakeShutdown();
        break;
    case EXAMPLE_BASIC_3D:
        Basic3DShutdown();
        break;
    case EXAMPLE_SHAPES:
        ShapesShutdown();
        break;
    case EXAMPLE_TEXT:
        TextDemoShutdown();
        break;
    case EXAMPLE_IMAGES:
        ImagesShutdown();
        break;
    case EXAMPLE_RENDER_FX:
        RenderFxShutdown();
        break;
    case EXAMPLE_CAMERA_2D:
        CameraDemoShutdown();
        break;
    case EXAMPLE_AUDIO:
        AudioDemoShutdown();
        break;
    case EXAMPLE_PARTICLES:
        ParticlesShutdown();
        break;
    case EXAMPLE_LIGHTING_3D:
        Lighting3DShutdown();
        break;
    default:
        break;
    }
    currentScreen = EXAMPLE_CATALOG;
    SetWindowTitle("SarGPU Examples");
}

static void DrawCard(Rectangle card, int number, const ExampleCard *example) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), card);
    DrawRectangleRounded(card, .12f, 10, hover ? (Color){29, 44, 68, 255} : (Color){20, 31, 49, 255});
    DrawRectangleRoundedLinesEx(card, .12f, 10, hover ? 3 : 2, hover ? example->accent : (Color){54, 75, 103, 255});
    DrawCircle((int)card.x + 58, (int)card.y + 62, 29, example->accent);
    const char *numberText = TextFormat("%d", number % 10);
    int numberWidth = MeasureText(numberText, 26);
    DrawText(numberText, (int)card.x + 58 - numberWidth / 2, (int)card.y + 47, 26, (Color){8, 13, 22, 255});
    DrawFittedText(example->title, (int)card.x + 105, (int)card.y + 15, 29, (int)card.width - 130, RAYWHITE);
    DrawFittedText(example->description, (int)card.x + 105, (int)card.y + 53, 19, (int)card.width - 130, LIGHTGRAY);
    DrawFittedText(example->features, (int)card.x + 105, (int)card.y + 82, 17, (int)card.width - 130, hover ? example->accent : GRAY);
}

static void DrawCatalog(void) {
    Rectangle bounds[10];
    for (int i = 0; i < 10; i++) {
        bounds[i] = (Rectangle){120.0f + (i % 2) * 880.0f, 220.0f + (i / 2) * 153.0f, 820, 126};
        if (Clicked(bounds[i]) || IsKeyPressed(cards[i].key)) {
            OpenExample(cards[i].screen);
            return;
        }
    }
    BeginDrawing();
    ClearBackground((Color){8, 13, 23, 255});
    DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){18, 35, 60, 255}, (Color){5, 9, 17, 255});
    DrawFittedText("SARGPU EXAMPLES", 120, 58, 58, SCREEN_WIDTH - 240, RAYWHITE);
    DrawFittedText("Ten focused demos. Click a card or press its number key.", 124, 132, 25, SCREEN_WIDTH - 248, LIGHTGRAY);
    for (int i = 0; i < 10; i++) DrawCard(bounds[i], i + 1, &cards[i]);
    DrawText("ESC or the EXAMPLES button returns to this catalog", 120, 1004, 18, DARKGRAY);
    DrawFPS(1800, 24);
    EndDrawing();
}

static void UpdateCurrentExample(void) {
    switch (currentScreen) {
    case EXAMPLE_SNAKE:
        SnakeUpdate();
        break;
    case EXAMPLE_BASIC_3D:
        Basic3DUpdate();
        break;
    case EXAMPLE_SHAPES:
        ShapesUpdate();
        break;
    case EXAMPLE_TEXT:
        TextDemoUpdate();
        break;
    case EXAMPLE_IMAGES:
        ImagesUpdate();
        break;
    case EXAMPLE_RENDER_FX:
        RenderFxUpdate();
        break;
    case EXAMPLE_CAMERA_2D:
        CameraDemoUpdate();
        break;
    case EXAMPLE_AUDIO:
        AudioDemoUpdate();
        break;
    case EXAMPLE_PARTICLES:
        ParticlesUpdate();
        break;
    case EXAMPLE_LIGHTING_3D:
        Lighting3DUpdate();
        break;
    default:
        DrawCatalog();
        break;
    }
}

static void AppFrame(void) {
    if (currentScreen != EXAMPLE_CATALOG && (IsKeyPressed(KEY_ESCAPE) || Clicked(backButton))) {
        CloseExample();
        DrawCatalog();
        return;
    }
    UpdateCurrentExample();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SarGPU Examples");
    if (!IsWindowReady()) return 1;
    SetWindowMinSize(1280, 720);
    SetExitKey(KEY_NULL);
    SetTargetFPS(120);
    InitAudioDevice();
    RunMainLoop(AppFrame);
    return SarGPUHadError() ? 1 : 0;
}
