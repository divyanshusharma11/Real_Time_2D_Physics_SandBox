#include "raylib.h"
#include "solver.hpp"


int main() {
    InitWindow(800, 600, "Physics Sandbox");   // 800x600 ki window kholo
    SetTargetFPS(60);                          // 1 second mein 60 frames


    Solver solver;
    float spawnTimer=0;
    const int maxBall=300;

    while (!WindowShouldClose()) {     // jab tak window band na ho
        float dt = GetFrameTime();     // pichle frame se kitna time hua
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
        
        DrawFPS(10, 10);                  // kone mein FPS dikhao
        EndDrawing();
    }
    CloseWindow();
}
