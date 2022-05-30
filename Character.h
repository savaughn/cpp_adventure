#include "raylib.h"

struct AnimData
{
    int frame;
    float runningTime;
    const float updateTime;
    const int maxFrame;
};

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void tick(float deltaTime);
    void unloadTextures() {
        UnloadTexture(texture);
        UnloadTexture(idle);
        UnloadTexture(run);
    };
    void undoMovement() {
        worldPos = worldPositionLastFrame;
    };

private:
    void drawPlayer(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData);
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    AnimData animData{
        0,
        0.0f,
        1.f / 12.f,
        6
    };
    const float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPositionLastFrame{};
};