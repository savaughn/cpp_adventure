#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "WindowManagement.h"

class Character : public BaseCharacter {
public:
    Character(screenResolution screenRes, Vector2 startingWorldPos);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() const {
        return weaponCollisionRec;
    };
    float getHealth() const {
        return health;
    };
    void takeDamage(float damage);
private:
    int windowWidth;
    int windowHeight;
    Texture2D weapon{LoadTexture("romfs:/resources/characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif