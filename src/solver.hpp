#pragma once
#include "raylib.h"
#include "raymath.h"
#include<vector>
using namespace std;

struct Particle{
    Vector2 pos;
    Vector2 oldPos;
    Vector2 acc;
    float radius;
    Color color;

    Particle(Vector2 pos,  float radius,Color color){
        this->pos=pos;
        this->oldPos=pos;
        // this->acc={0,0};
        this->acc.x=0;
        this->acc.y=0;
        this->radius=radius;
        this->color=color;
    }

    void update(float dt   ){
        Vector2 velocity= pos-oldPos;
        oldPos=pos;
        pos=pos+velocity+acc*(dt*dt);
        acc={0,0};
 }

 void Accelerate(Vector2 a){
    acc=acc+a;
 }

};

class Solver{
    public:
    Vector2 gravity;
    Vector2 Centre;
    float boundaryRadius;
    int subSteps;
    float SubDT;

    Solver() {
        gravity = {0, 1000};
        Centre = {400, 300};
        boundaryRadius = 280;
        subSteps = 8;
        

    }


    void addParticle(Vector2 pos, float radius, Color color){
        particle.emplace_back(pos, radius, color);

    }




    void updateDt(float dt){
        SubDT=dt/subSteps;
        for(int i = 0 ; i<subSteps;i++){

        applyGravity();
        applyBoundary();
        solveCollisions();
        updatePosition(SubDT);
            
        }


    }

        const vector<Particle>& getParticles() const {
        return particle;
    }


    private:



    vector<Particle>particle;

    void applyGravity(){
        for(int i = 0 ; i<particle.size();i++){
            particle[i].Accelerate(gravity);
        }

    }

    void updatePosition(float dt){
   
                for(int i = 0 ; i<particle.size();i++){
            particle[i].update(dt);
        }

    }

    void  applyBoundary(){
        for(int i = 0 ; i<particle.size(); i++){
            Particle &p=particle[i];
            Vector2 toP= p.pos-Centre;
            float dist=Vector2Length(toP);  //calculate distance between (x1,y1) and (x2,y2)
            float maxDist=boundaryRadius-p.radius;
            if(dist>maxDist){ //ball moved outside the boundary wall
                Vector2 n = toP/dist; //normalize the vector
                p.pos=Centre+n*maxDist; //move the ball back to the boundary wall

            }
        }


    }

    void solveCollisions(){
        for(int i = 0 ; i<particle.size();i++){
            for(int j =i+1;j<particle.size();j++)
            {
                Particle &b1=particle[i];
                Particle &b2=particle[j];

                float radiusSum=b1.radius+b2.radius;  //min dist, dist between shhould not be smaller than this size
                Vector2 distBtwn2Balls=b1.pos-b2.pos;
                float dist= Vector2Length(distBtwn2Balls); //actual diff

                if(radiusSum>dist && dist>0.0001f){//collision happened
                    //1. calculate the normal vector
                    Vector2 n= distBtwn2Balls/dist; //normalize the vector
                    float overlap= radiusSum-dist; //how much they are overlapping
                    //2.now we will separate the balls, half overlap for each ball
                    b1.pos=b1.pos+n*(overlap*0.5f); //move the ball apart, half overlap for b1
                    b2.pos=b2.pos-n*(overlap*0.5f); //move the ball back , half overlap for b2

                }
            }
        }
    }




};
