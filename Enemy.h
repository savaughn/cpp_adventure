#include "raylib.h"

struct AnimDataEnemy
{
    int frame;
    float runningTime;
    const float updateTime;
    const int maxFrame;
};

class Enemy {
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void tick(float deltaTime);
    void undoMovement() {
        worldPos = worldPositionLastFrame;
    };
    Rectangle getCollisionRec();

private:
    void drawTexture(Texture2D texture, Vector2 texturePosition, Vector2 direction, float rightLeft, AnimDataEnemy animData);
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    AnimDataEnemy animData{
        0,
        0.0f,
        1.f / 12.f,
        6
    };
    const float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPositionLastFrame{};
    float scale{4.f};
};