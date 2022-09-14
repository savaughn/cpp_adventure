#pragma once

#include "raylib.h"

struct AnimData
{
    int frame;
    float runningTime;
    const float updateTime;
    const int maxFrame;
};

class BaseCharacter
{
public:
    BaseCharacter();
    virtual void tick(float deltaTime);
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void unloadTextures()
    {
        UnloadTexture(texture);
        UnloadTexture(idle);
        UnloadTexture(run);
    };
    void undoMovement()
    {
        worldPos = worldPositionLastFrame;
    };
    Rectangle getCollisionRec();
    void drawCollisionDebug()
    {
        debugMode = !debugMode;
    };
    bool isDebugActive()
    {
        return debugMode;
    };
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {
        return alive;
    };
    void setAlive(bool alive) {
        this->alive = alive;
    };
    Vector2 worldPos{};
    
protected:
    void drawCharacter(Texture2D sprite, Vector2 spritePosition, Vector2 direction, float rightLeft, AnimData animData);
    Texture2D texture{LoadTexture("assets/frog/frog-run.png")};
    Texture2D idle{LoadTexture("assets/frog/frog-idle.png")};
    Texture2D run{LoadTexture("assets/frog/frog-run.png")};
    AnimData animData{
        0,
        0.0f,
        1.f / 8.f,
        4
    };
    float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPositionLastFrame{};
    float scale{8.f};
    bool debugMode{false};
    Vector2 velocity{};
    float rightLeft{1.f};

private:
    bool alive{true};
};
