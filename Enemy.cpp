#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) :
    worldPos(pos),
    texture(idle_texture),
    idle(idle_texture),
    run(run_texture)
{
    width = texture.width / animData.maxFrame;
    height = texture.height;
}

void Enemy::tick(float deltaTime) {
    worldPositionLastFrame = worldPos;
    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }
    drawTexture(texture, worldPos, {1.f, 0.f}, 1.f, animData);
}

void Enemy::drawTexture(Texture2D texture, Vector2 texturePosition, Vector2 direction, float rightLeft, AnimDataEnemy animData)
{
    rightLeft = direction.x < 0.f ? -1.f : 1.f;
    Rectangle sourceRectangle = {
        animData.frame * static_cast<float>(texture.width) / 6.f,
        0.f, (rightLeft) * static_cast<float>(texture.width) / 6.f,
        static_cast<float>(texture.height)};
    Rectangle destinationRectangle = {
        texturePosition.x, texturePosition.y,
        scale * static_cast<float>(texture.width) / 6.f,
        scale * static_cast<float>(texture.height)
    };
    DrawTexturePro(texture, sourceRectangle, destinationRectangle, {0, 0}, 0.f, WHITE);
}

Rectangle Enemy::getCollisionRec() {
    return Rectangle{
        screenPos.x + (width * scale * (0.5f)/2.f),
        screenPos.y + height * scale * 0.75f,
        width * scale * 0.5f,
        height * scale / 8.f
    };
}
