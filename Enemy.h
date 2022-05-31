#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    void tick(float deltaTime);
    void setTarget(Character* character) {
        target = character;
    }
private:
    Character* target;
};