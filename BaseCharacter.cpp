#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

}

void BaseCharacter::drawCharacter(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData)
{
    rightLeft = direction.x < 0.f ? -1.f : 1.f;
    Rectangle sourceRectangle = {
        animData.frame * static_cast<float>(knight.width) / 6.f,
        0.f, (rightLeft) * static_cast<float>(knight.width) / 6.f,
        static_cast<float>(knight.height)};
    Rectangle destinationRectangle = {
        knightPosition.x, knightPosition.y,
        scale * static_cast<float>(knight.width) / 6.f,
        scale * static_cast<float>(knight.height)
    };
    DrawTexturePro(knight, sourceRectangle, destinationRectangle, {0, 0}, 0.f, WHITE);
}

Rectangle BaseCharacter::getCollisionRec() {
    return Rectangle{
        getScreenPos().x + (width * scale * (0.5f)/2.f),
        getScreenPos().y + height * scale * 0.85f,
        width * scale * 0.5f,
        height * scale / 8.f
    };
}

void BaseCharacter::tick(float deltaTime) {
    worldPositionLastFrame = worldPos;
    

    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
    }

    texture = Vector2Length(velocity) ? run : idle;

    drawCharacter(texture, getScreenPos(), velocity, 1.f, animData);
    
    if (IsKeyDown(KEY_F1)) {
        drawCollisionDebug();
    }
    
    if (debugMode) {
        auto [a,b,c,d] = getCollisionRec();
        DrawRectangle(a,b,c,d, GREEN);
    }

    velocity = {0.f, 0.f};
}