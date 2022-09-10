#include "Character.h"

Character::Character(int winWidth, int winHeight)
{
    windowWidth = winWidth;
    windowHeight = winHeight;
    width = texture.width / animData.maxFrame;
    height = texture.height;
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;

    if (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    weaponCollisionRec = {
        getScreenPos().x + 10,
        getScreenPos().y + 30,
        static_cast<float>(width * scale * 0.75),
        static_cast<float>(height * scale * 0.5)
    };
    
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
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };  
}

void Character::takeDamage(float damage)
{
    if (!getIsCharacterInvicible()) {health -= damage;}
    if (health <= 0)
    {
        health = 0;
        setAlive(false);
    }
}