#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Particle
{
    Vector2 pos;
    Vector2 oldPos;
    Vector2 acc;
    float radius;
    Color color;

    Particle(Vector2 pos, float radius, Color color)
    {
        this->pos = pos;
        this->oldPos = pos;
        // this->acc={0,0};
        this->acc.x = 0;
        this->acc.y = 0;
        this->radius = radius;
        this->color = color;
    }

    void update(float dt)
    {
        Vector2 velocity = pos - oldPos;
        oldPos = pos;
        pos = pos + velocity + acc * (dt * dt);
        acc = {0, 0};
    }

    void Accelerate(Vector2 a)
    {
        acc = acc + a;
    }
};

class Solver
{
public:
    Vector2 gravity;
    Vector2 Centre;
    float boundaryRadius;
    int subSteps;
    float SubDT;
    bool useGrid;

    Solver()
    {
        gravity = {0, 1000};
        Centre = {400, 300};
        boundaryRadius = 280;
        subSteps = 8;
        createGrid();
        useGrid=true;
        

    }

    void addParticle(Vector2 pos, float radius, Color color)
    {
        particle.emplace_back(pos, radius, color);
    }

    void updateDt(float dt)
    {
        SubDT = dt / subSteps;
        for (int i = 0; i < subSteps; i++)
        {

            applyGravity();
            applyBoundary();
            if(useGrid){
                fillGrid();
                solveCollisiongrid();
            }
            else solveCollisions();

            updatePosition(SubDT);
        }
    }

    const vector<Particle> &getParticles() const
    {
        return particle;
    }

private:
    int cellsize;
    int cols;
    int rows;
    // vector<Particle>cells;
    vector<vector<int>> cells;

    vector<Particle> particle;

    void applyGravity()
    {
        for (int i = 0; i < particle.size(); i++)
        {
            particle[i].Accelerate(gravity);
        }
    }

    void updatePosition(float dt)
    {

        for (int i = 0; i < particle.size(); i++)
        {
            particle[i].update(dt);
        }
    }

    void applyBoundary()
    {
        for (int i = 0; i < particle.size(); i++)
        {
            Particle &p = particle[i];
            Vector2 toP = p.pos - Centre;
            float dist = Vector2Length(toP); // calculate distance between (x1,y1) and (x2,y2)
            float maxDist = boundaryRadius - p.radius;
            if (dist > maxDist)
            {                                 // ball moved outside the boundary wall
                Vector2 n = toP / dist;       // normalize the vector
                p.pos = Centre + n * maxDist; // move the ball back to the boundary wall
            }
        }
    }

    void solveCollisions()
    {
        for (int i = 0; i < particle.size(); i++)
        {
            for (int j = i + 1; j < particle.size(); j++)
            {
                collide(i, j);
            }
        }
    }

    void collide(int i, int j)
    {
        Particle &b1 = particle[i];
        Particle &b2 = particle[j];

        float radiusSum = b1.radius + b2.radius; // min dist, dist between shhould not be smaller than this size
        Vector2 distBtwn2Balls = b1.pos - b2.pos;
        float dist = Vector2Length(distBtwn2Balls); // actual diff

        if (radiusSum > dist && dist > 0.0001f)
        { // collision happened
            // 1. calculate the normal vector
            Vector2 n = distBtwn2Balls / dist; // normalize the vector
            float overlap = radiusSum - dist;  // how much they are overlapping
            // 2.now we will separate the balls, half overlap for each ball
            b1.pos = b1.pos + n * (overlap * 0.5f); // move the ball apart, half overlap for b1
            b2.pos = b2.pos - n * (overlap * 0.5f); // move the ball back , half overlap for b2
        }
    }

    void solveCollisiongrid()
    {
        for (int r = 0; r <= rows - 1; r++)
        {
            for (int c = 0; c <= cols - 1; c++)
            {
                int index = r * cols + c;
                if (cells[index].size() == 0)
                    continue;
                else
                {
                    // stage2
                    for (int dr = -1; dr <= 1; dr++)
                    { // select roww
                        for (int dc = -1; dc <= 1; dc++)
                        { // select column
                            int nc= c+dc;
                            int nr=r+dr;
                            if(nr<0 || nr>rows-1 || nc<0 || nc>cols-1)continue;
                            int nbox=nr*cols+nc;

                            for(int a= 0 ;a<cells[index].size();a++){
                                for(int b = 0 ; b<cells[nbox].size();b++){
                                     int i = cells[index][a];
                                    int j = cells[nbox][b];
                                    if (i < j)
                                        collide(i, j);

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void clearGrid()
    {
        for (int i = 0; i < cells.size(); i++)
        {
            cells[i].clear();
            // we have to clear sub vectors not main parent vector
        }
    }

    void fillGrid()
    {
        clearGrid();

        for (int i = 0; i < particle.size(); i++)
        {
            int index = calculateGridIndex(particle[i]);
            cells[index].push_back(i);
        }
    }

    int calculateGridIndex(Particle p)
    {
        int c = p.pos.x / 8;
        int r = p.pos.y / 8;

        c = clamp(c, 0, cols - 1);
        r = clamp(r, 0, rows - 1);

        int index = r * 100 + c;
        return index;
    }

    // our window is 800 px wide and 600 px tall,
    // now radius of 1 ball is 4, whole width of ball = diameter=2r=2*4=8
    // 1 balll willl occupy 8 x 8 px. we will create each cell in grid of size of 1 ball
    void createGrid()
    {
        cellsize = 8;
        rows = 600 / cellsize;
        cols = 800 / cellsize;
        int n = (cols) * (rows); // total number of cells in grid=7500,
        cells.resize(n);         // resize the vector to hold 7500 cells
    }
};
