
#pragma once

#include "raylib.h"
#include "solver.hpp"

// ==========================================
// 1. SPEED-BASED BALL COLOR
// ==========================================

// Slow  = Blue
// Medium = Green / Yellow
// Fast  = Red

inline Color speedToColor(float speed) {

    // Normalize speed between 0 and 1
    float t = speed / 2.0f;

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // Convert speed into HSV hue
    // 240 = Blue, 120 = Green
    // 60 = Yellow, 0 = Red

    float hue = 240.0f * (1.0f - t);

    return ColorFromHSV(hue, 0.8f, 1.0f);
}


// ==========================================
// 2. HEADS-UP DISPLAY (HUD)
// ==========================================

inline void drawHUD(int ballCount, bool useGrid) {

    // Display current FPS
    DrawFPS(10, 10);

    // Display total number of balls
    DrawText(
        TextFormat("Balls: %d", ballCount),
        10, 35, 20, RAYWHITE
    );

    // Display mouse control instructions
    DrawText(
        "Left click: spawn ball",
        10, 60, 16, GRAY
    );

    DrawText(useGrid? "Mode: Grid(G)" : "Mode: Brute force(G)", 10, 85, 20, YELLOW);
}
