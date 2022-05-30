#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) {
    width = texture.width / animData.maxFrame;
    height = texture.height;
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

void Character::drawPlayer(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData)
{
    rightLeft = direction.x < 0.f ? -1.f : 1.f;
    Rectangle sourceRectangle = {animData.frame * (float)knight.width / 6.f, 0.f, (rightLeft) * (float)knight.width / 6.f, (float)knight.height};
    Rectangle destinationRectangle = {knightPosition.x, knightPosition.y, 4.0f * (float)knight.width / 6.f, 4.0f * (float)knight.height};
    DrawTexturePro(knight, sourceRectangle, destinationRectangle, {0, 0}, 0.f, WHITE);
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

    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }
    texture = Vector2Length(direction) ? run : idle;

    drawPlayer(texture, screenPos, direction, 1.f, animData);
}