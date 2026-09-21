#include "examples.h"

#define PARTICLE_COUNT 320
typedef struct DemoParticle {
    Vector2 position, velocity;
    float life, size;
    Color color;
} DemoParticle;
static DemoParticle particles[PARTICLE_COUNT];
static int particleCursor;

static void SpawnParticle(Vector2 origin, int count) {
    for (int n = 0; n < count; n++) {
        DemoParticle *p = &particles[particleCursor++ % PARTICLE_COUNT];
        float angle = (float)GetRandomValue(0, 628) * .01f, speed = (float)GetRandomValue(80, 520);
        p->position = origin;
        p->velocity = (Vector2){Sin(angle + 1.5707963f) * speed, Sin(angle) * speed};
        p->life = (float)GetRandomValue(60, 150) * .01f;
        p->size = (float)GetRandomValue(4, 14);
        p->color = ColorFromHSV((float)GetRandomValue(0, 359), .72f, 1);
    }
}

void ParticlesInit(void) {
    SetWindowTitle("SarGPU Examples - Particles");
    for (int i = 0; i < PARTICLE_COUNT; i++) particles[i].life = 0;
    particleCursor = 0;
    SetRandomSeed((unsigned int)(GetTime() * 100000));
}
void ParticlesShutdown(void) {}

void ParticlesUpdate(void) {
    float dt = GetFrameTime();
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) SpawnParticle(mouse, 8);
    if (IsKeyPressed(KEY_SPACE)) SpawnParticle((Vector2){960, 500}, 140);
    int alive = 0;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        DemoParticle *p = &particles[i];
        if (p->life <= 0) continue;
        p->life -= dt;
        if (p->life <= 0) continue;
        alive++;
        p->velocity.y += 260 * dt;
        p->position.x += p->velocity.x * dt;
        p->position.y += p->velocity.y * dt;
        if (p->position.x < p->size || p->position.x > 1920 - p->size) {
            p->velocity.x *= -.82f;
            p->position.x = p->position.x < p->size ? p->size : 1920 - p->size;
        }
        if (p->position.y > 1010 - p->size) {
            p->position.y = 1010 - p->size;
            p->velocity.y *= -.72f;
        }
    }
    BeginDrawing();
    ClearBackground((Color){4, 7, 15, 255});
    DrawRectangleGradientV(0, 0, 1920, 1080, (Color){16, 25, 45, 255}, (Color){3, 5, 11, 255});
    BeginBlendMode(BLEND_ADDITIVE);
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        DemoParticle *p = &particles[i];
        if (p->life > 0) DrawCircleV(p->position, p->size, (Color){p->color.r, p->color.g, p->color.b, (unsigned char)(p->life > 1 ? 180 : p->life * 180)});
    }
    EndBlendMode();
    DrawLine(0, 1010, 1920, 1010, (Color){80, 110, 150, 255});
    DrawRectangleRounded((Rectangle){40, 40, 720, 145}, .12f, 12, (Color){5, 8, 18, 220});
    DrawText("PARTICLE SANDBOX", 65, 55, 38, RAYWHITE);
    DrawText("Hold left mouse to emit | SPACE for a burst", 66, 105, 20, LIGHTGRAY);
    DrawText(TextFormat("%d / %d particles alive", alive, PARTICLE_COUNT), 66, 137, 18, GOLD);
    DrawCircleV(mouse, 12, WHITE);
    DrawExampleBackButton();
    DrawFPS(1800, 82);
    EndDrawing();
}
