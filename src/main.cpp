#include "raylib.h"

int main() {
    InitWindow(800, 600, "Physics Sandbox");   // 800x600 ki window kholo
    SetTargetFPS(60);                          // 1 second mein 60 frames

    Vector2 pos = {400, 100};   // ball ki position (x, y)
    float vy = 0;               // ball ki neeche ki speed

    while (!WindowShouldClose()) {     // jab tak window band na ho
        float dt = GetFrameTime();     // pichle frame se kitna time hua
        vy += 980 * dt;                // gravity: speed badhti jaati hai
        pos.y += vy * dt;              // speed se position badlo
        if (pos.y > 580) {             // zameen se takrayi?
            pos.y = 580;
            vy *= -0.7f;               // ulta uchhlo, 30% energy kam
        }

        BeginDrawing();
        ClearBackground(BLACK);           // screen kaali karo
        DrawCircleV(pos, 20, SKYBLUE);    // ball banao
        DrawFPS(10, 10);                  // kone mein FPS dikhao
        EndDrawing();
    }
    CloseWindow();
}
