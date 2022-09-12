#ifndef WINDOWMANAGEMENT_H
#define WINDOWMANAGEMENT_H

#include "Character.h"

Character::Character(screenResolution screenRes, Vector2 startingWorldPos)
{
    auto [ width, height ]  = screenRes;
    windowWidth = width;
    windowHeight = height;
    width = texture.width / animData.maxFrame;
    height = texture.height;
    worldPos = startingWorldPos;
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);
    if (debugMode) {
        DrawRectangleLines(
            weaponCollisionRec.x,
            weaponCollisionRec.y,
            weaponCollisionRec.width,
            weaponCollisionRec.height, 
            RED
        );
    }
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height) - 200.f
    };  
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        setAlive(false);
    }
}

#endif