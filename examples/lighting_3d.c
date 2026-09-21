#include "examples.h"

static Camera3D lightCamera;
static Model lightModels[3];
static bool fogEnabled = true, pbrEnabled = true;

void Lighting3DInit(void) {
    SetWindowTitle("SarGPU Examples - Lighting 3D");
    lightCamera = (Camera3D){{13, 9, 13}, {0, 1, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    lightModels[0] = LoadModelFromMesh(GenMeshSphere(1.5f, 24, 32));
    lightModels[1] = LoadModelFromMesh(GenMeshTorus(1.6f, .45f, 32, 16));
    lightModels[2] = LoadModelFromMesh(GenMeshCube(2.6f, 2.6f, 2.6f));
    SetAmbientLight((Color){90, 105, 140, 255}, .28f);
    SetPBRMode(true);
    SetFog(FOG_LINEAR, (Color){22, 30, 48, 255}, 10, 30, .04f);
}
void Lighting3DShutdown(void) {
    for (int i = 0; i < 3; i++) {
        if (IsModelValid(lightModels[i])) UnloadModel(lightModels[i]);
        lightModels[i] = (Model){0};
    }
    DisableFog();
    SetPBRMode(false);
    SetAmbientLight(WHITE, 1);
}

void Lighting3DUpdate(void) {
    float t = (float)GetTime();
    if (IsKeyPressed(KEY_F)) {
        fogEnabled = !fogEnabled;
        if (fogEnabled)
            SetFog(FOG_LINEAR, (Color){22, 30, 48, 255}, 10, 30, .04f);
        else
            DisableFog();
    }
    if (IsKeyPressed(KEY_P)) {
        pbrEnabled = !pbrEnabled;
        SetPBRMode(pbrEnabled);
    }
    Vector3 lightPos = {Sin(t * .8f + 1.5707963f) * 7, 5, Sin(t * .8f) * 7};
    SetLight3D(0, CreateLight3D(LIGHT_POINT, lightPos, (Vector3){0, 0, 0}, (Color){255, 185, 105, 255}, 4.5f, 18));
    SetLight3D(1, CreateLight3D(LIGHT_DIRECTIONAL, (Vector3){-4, 8, -5}, (Vector3){0, 0, 0}, (Color){125, 170, 255, 255}, 1.5f, 0));
    BeginDrawing();
    ClearBackground((Color){22, 30, 48, 255});
    BeginMode3D(lightCamera);
    DrawPlane((Vector3){0, 0, 0}, (Vector2){35, 35}, (Color){105, 110, 120, 255});
    DrawGrid(30, 1);
    DrawModelEx(lightModels[0], (Vector3){-4, 1.6f, 0}, (Vector3){0, 1, 0}, t * 22, (Vector3){1, 1, 1}, (Color){225, 70, 75, 255});
    DrawModelEx(lightModels[1], (Vector3){0, 2.0f, 0}, (Vector3){1, 1, 0}, t * 35, (Vector3){1, 1, 1}, (Color){70, 210, 155, 255});
    DrawModelEx(lightModels[2], (Vector3){4, 1.4f, 0}, (Vector3){0, 1, 0}, t * 28, (Vector3){1, 1, 1}, (Color){80, 135, 255, 255});
    DrawSphere(lightPos, .22f, GOLD);
    DrawLine3D(lightPos, (Vector3){0, 0, 0}, (Color){255, 205, 105, 180});
    EndMode3D();
    DrawRectangleRounded((Rectangle){32, 32, 760, 160}, .12f, 12, (Color){4, 8, 16, 215});
    DrawText("LIGHTING 3D", 58, 50, 40, RAYWHITE);
    DrawText("Animated point light + directional fill", 58, 102, 21, LIGHTGRAY);
    DrawText(TextFormat("P: PBR %s    F: FOG %s", pbrEnabled ? "ON" : "OFF", fogEnabled ? "ON" : "OFF"), 58, 142, 21, GOLD);
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
