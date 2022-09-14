#pragma once

#include "Actor.h"
#include "raylib-cpp.hpp"

class Frog : public Actor {
    public:
        Frog();
        virtual bool update(bool onGround);	
        virtual void draw();        
        virtual raylib::Rectangle getBoundingBox();        
        virtual void MoveAway();        
        virtual void MoveLeft();        
        virtual void MoveRight();        
        virtual void MoveToward();        
        virtual void goNowhere();        
        virtual void doInteractWith();
        
    private:
        raylib::Vector2 getUpperLeftPosition();
        raylib::Texture2D run{LoadTexture("assets/frog/frog-run.png")}; 
        raylib::Texture2D idle{LoadTexture("assets/frog/frog-idle.png")};  
        raylib::Texture2D* texture = &idle;  
        raylib::Sound footstepSound;
        raylib::Sound landingSound;
        
        // Animation state
        unsigned numFrames;
        int frameWidth;
        unsigned frameDelay;
        unsigned frameDelayCounter;
        unsigned frameIndex;
        raylib::Rectangle frameRect;
        
        float jumpSpeed;
        float walkSpeed;
        
        bool isOnGround;
};