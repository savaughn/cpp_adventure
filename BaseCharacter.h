#include "raylib.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

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
    
protected:
    void drawCharacter(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData);
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    AnimData animData{
        0,
        0.0f,
        1.f / 12.f,
        6
    };
    float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPositionLastFrame{};
    float scale{4.f};
    bool debugMode{false};
    Vector2 velocity{};
    float rightLeft{1.f};

private:
    bool alive{true};
};
#endif