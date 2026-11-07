#include "raylib.h"
#include "solver.hpp"


int main() {
    InitWindow(800, 600, "Physics Sandbox");   // open an 800x600 window
    SetTargetFPS(60);                          // cap the frame rate at 60 FPS


    Solver solver;
    float spawnTimer=0;
    const int maxBall=300;

    while (!WindowShouldClose()) {     // run until the window is closed
        float dt = GetFrameTime();     // time since the last frame (seconds)
        spawnTimer=spawnTimer+dt;
        if(spawnTimer>0.05f && solver.getParticles().size()<maxBall){
            spawnTimer=0;
            solver.addParticle({400.0f + GetRandomValue(-50, 50), 100}, 10, SKYBLUE);

        }
        solver.updateDt(dt); //our physics

        BeginDrawing();
        ClearBackground(BLACK); 
        DrawCircleV(solver.Centre, solver.boundaryRadius, DARKGRAY); //OUR MAIN BOWL
         const     vector<Particle> &balls= solver.getParticles();
        for(int i = 0 ; i <balls.size();i++){
           
            

            DrawCircleV(balls[i].pos, balls[i].radius, balls[i].color);

        }         
        
        DrawFPS(10, 10);                  // show FPS in the top-left corner
        EndDrawing();
    }
    CloseWindow();
}
