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

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = Vector2{0.f, weapon.height * scale};
        offset = Vector2{35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = Vector2{weapon.width * scale, weapon.height * scale};
        offset = Vector2{25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }
    
    Rectangle source{
        0.f,
        0.f,
        static_cast<float>(weapon.width) * rightLeft,
        static_cast<float>(weapon.height)
    };

    Rectangle destination{
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y,
        weapon.width * scale,
        weapon.height * scale
    };
    DrawTexturePro(weapon, source, destination, origin, rotation, WHITE);
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
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        setAlive(false);
    }
}