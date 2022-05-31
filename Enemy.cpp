#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) {
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / animData.maxFrame;
    height = texture.height;
}

void Enemy::tick(float deltaTime) {
    worldPositionLastFrame = worldPos;
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }
    drawCharacter(texture, screenPos, {1.f, 0.f}, 1.f, animData);
}
