#include "examples.h"

static RenderTexture2D fxTarget;
static Shader fxShader;
static int fxTimeLocation;
static int fxStrengthLocation;

void RenderFxInit(void) {
    SetWindowTitle("SarGPU Examples - Render FX");
    fxTarget = LoadRenderTexture(960, 540);
    fxShader = LoadShaderFromMemory(0, "// @sargpu_uniform time 0\n"
                                       "// @sargpu_uniform strength 1\n"
                                       "struct V { @builtin(position) position: vec4f, @location(0) uv: vec2f, @location(1) color: vec4f };"
                                       "struct Uniforms { values: array<vec4f, 128> };"
                                       "@group(0) @binding(0) var smp: sampler; @group(0) @binding(1) var tex: texture_2d<f32>;"
                                       "@group(1) @binding(0) var<uniform> uniforms: Uniforms;"
                                       "@fragment fn fs(v: V) -> @location(0) vec4f {"
                                       " let t=uniforms.values[0].x; let amount=uniforms.values[4].x;"
                                       " let wave=sin(v.uv.y*38.0+t*3.0)*0.006*amount; let uv=vec2f(v.uv.x+wave,v.uv.y);"
                                       " let r=textureSample(tex,smp,uv+vec2f(0.004*amount,0.0)).r;"
                                       " let g=textureSample(tex,smp,uv).g; let b=textureSample(tex,smp,uv-vec2f(0.004*amount,0.0)).b;"
                                       " let edge=1.0-smoothstep(0.25,0.72,distance(v.uv,vec2f(0.5)));"
                                       " return vec4f(vec3f(r,g,b)*(0.72+0.28*edge),1.0)*v.color; }");
    fxTimeLocation = GetShaderLocation(fxShader, "time");
    fxStrengthLocation = GetShaderLocation(fxShader, "strength");
}

void RenderFxShutdown(void) {
    if (IsShaderValid(fxShader)) UnloadShader(fxShader);
    if (IsRenderTextureValid(fxTarget)) UnloadRenderTexture(fxTarget);
    fxShader = (Shader){0};
    fxTarget = (RenderTexture2D){0};
}

void RenderFxUpdate(void) {
    float time = (float)GetTime(), strength = .55f + .45f * Sin(time * .8f);
    SetShaderValue(fxShader, fxTimeLocation, &time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(fxShader, fxStrengthLocation, &strength, SHADER_UNIFORM_FLOAT);
    BeginTextureMode(fxTarget);
    ClearBackground((Color){9, 15, 32, 255});
    DrawRectangleGradientV(0, 0, 960, 540, (Color){24, 38, 84, 255}, (Color){8, 11, 25, 255});
    for (int i = 0; i < 14; i++) {
        float x = 80 + i * 70.0f, y = 270 + Sin(time * 2 + i * .65f) * 145;
        DrawCircle((int)x, (int)y, 28 + i % 3 * 9, ColorFromHSV((float)i * 27, 0.72f, 1));
    }
    DrawText("OFFSCREEN SCENE", 250, 70, 46, RAYWHITE);
    DrawText("rendered at 960 x 540", 325, 125, 23, LIGHTGRAY);
    DrawPoly((Vector2){480, 330}, 8, 100, time * 38, (Color){255, 200, 80, 230});
    EndTextureMode();
    BeginDrawing();
    ClearBackground(BLACK);
    BeginShaderMode(fxShader);
    DrawTexturePro(fxTarget.texture, (Rectangle){0, 0, 960, 540}, (Rectangle){0, 0, 1920, 1080}, (Vector2){0}, 0, WHITE);
    EndShaderMode();
    DrawRectangleRounded((Rectangle){40, 40, 690, 155}, .12f, 10, (Color){0, 0, 0, 195});
    DrawRectangleRoundedLinesEx((Rectangle){40, 40, 690, 155}, .12f, 10, 2, (Color){65, 105, 145, 230});
    DrawText("RENDER FX", 65, 55, 38, RAYWHITE);
    DrawText("OFFSCREEN TARGET  960 X 540", 66, 105, 19, LIGHTGRAY);
    DrawText(TextFormat("WGSL POST PROCESS / STRENGTH %.2f", strength), 66, 144, 19, (Color){120, 230, 255, 255});
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
