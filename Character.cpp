#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / animData.maxFrame;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{

    worldPositionLastFrame = worldPos;

    Vector2 direction{0.f, 0.f};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
    }

    if (IsKeyDown(KEY_F1)) {
        drawCollisionDebug();
    }

    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }
    texture = Vector2Length(direction) ? run : idle;

    drawCharacter(texture, screenPos, direction, 1.f, animData);
    if (debugMode) {
        auto [a,b,c,d] = getCollisionRec();
        DrawRectangle(a,b,c,d, GREEN);
    }
}