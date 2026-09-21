#include "examples.h"

static Sound tones[4];
static float audioMaster = .8f;

static Sound AudioTone(float frequency, float seconds) {
    enum { RATE = 44100 };
    int frames = (int)(RATE * seconds);
    short *samples = MemAlloc((unsigned int)(frames * sizeof(short)));
    if (!samples) return (Sound){0};
    for (int i = 0; i < frames; i++) {
        float phase = 6.2831853f * frequency * i / RATE, fade = 1.0f - (float)i / frames;
        samples[i] = (short)(Sin(phase) * Sin(phase * .5f) * fade * 28000.0f);
    }
    Wave wave = {(unsigned int)frames, RATE, 16, 1, samples};
    Sound sound = LoadSoundFromWave(wave);
    MemFree(samples);
    return sound;
}

void AudioDemoInit(void) {
    SetWindowTitle("SarGPU Examples - Audio Lab");
    float notes[4] = {261.63f, 329.63f, 392.0f, 523.25f};
    for (int i = 0; i < 4; i++) {
        tones[i] = AudioTone(notes[i], .42f);
        SetSoundPan(tones[i], .2f + i * .2f);
    }
    SetMasterVolume(audioMaster);
}
void AudioDemoShutdown(void) {
    for (int i = 0; i < 4; i++) {
        if (IsSoundValid(tones[i])) UnloadSound(tones[i]);
        tones[i] = (Sound){0};
    }
    SetMasterVolume(1);
}

void AudioDemoUpdate(void) {
    int keys[4] = {KEY_Z, KEY_X, KEY_C, KEY_V};
    const char keyLabels[4] = {'Z', 'X', 'C', 'V'};
    const char *names[4] = {"C  261 Hz", "E  330 Hz", "G  392 Hz", "C  523 Hz"};
    Rectangle pads[4];
    for (int i = 0; i < 4; i++) pads[i] = (Rectangle){150 + i * 420.0f, 310, 350, 390};
    for (int i = 0; i < 4; i++)
        if (IsKeyPressed(keys[i]) || (CheckCollisionPointRec(GetMousePosition(), pads[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) PlaySound(tones[i]);
    if (IsKeyDown(KEY_UP)) {
        audioMaster += GetFrameTime() * .5f;
        if (audioMaster > 1) audioMaster = 1;
        SetMasterVolume(audioMaster);
    }
    if (IsKeyDown(KEY_DOWN)) {
        audioMaster -= GetFrameTime() * .5f;
        if (audioMaster < 0) audioMaster = 0;
        SetMasterVolume(audioMaster);
    }
    BeginDrawing();
    ClearBackground((Color){12, 10, 18, 255});
    DrawRectangleGradientV(0, 0, 1920, 1080, (Color){65, 28, 35, 255}, (Color){10, 8, 18, 255});
    DrawText("AUDIO LAB", 70, 50, 48, RAYWHITE);
    DrawText("Click a pad or use Z X C V / Up and Down change master volume", 72, 112, 22, LIGHTGRAY);
    for (int i = 0; i < 4; i++) {
        bool active = IsSoundPlaying(tones[i]), hover = CheckCollisionPointRec(GetMousePosition(), pads[i]);
        Color color = ColorFromHSV(15 + i * 42, active ? .9f : .6f, active ? 1 : .8f);
        DrawRectangleRounded(pads[i], .12f, 16, hover ? ColorBrightness(color, .2f) : color);
        DrawRectangleRoundedLinesEx(pads[i], .12f, 16, active ? 8 : 3, RAYWHITE);
        DrawText(TextFormat("%c", keyLabels[i]), (int)pads[i].x + 145, 365, 58, (Color){25, 15, 25, 255});
        DrawText(names[i], (int)pads[i].x + 78, 610, 25, (Color){25, 15, 25, 255});
        for (int b = 0; b < 8; b++) {
            float level = active ? (.25f + .75f * (Sin((float)GetTime() * 12 + b) + 1) * .5f) : .08f;
            DrawRectangle((int)pads[i].x + 42 + b * 34, 735 - (int)(level * 130), 20, (int)(level * 130), color);
        }
    }
    DrawText(TextFormat("MASTER VOLUME  %d%%", (int)(audioMaster * 100)), 150, 875, 28, RAYWHITE);
    DrawRectangle(150, 925, 800, 22, (Color){45, 45, 55, 255});
    DrawRectangle(150, 925, (int)(800 * audioMaster), 22, GOLD);
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
