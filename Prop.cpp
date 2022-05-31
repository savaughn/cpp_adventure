#include "raylib.h"
#include "raymath.h"
#include "Prop.h"
#include "BaseCharacter.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex) {

}

void Prop::Render(Vector2 knightPos, bool isDebugActive)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, {}, scale, WHITE);

    if (isDebugActive) {
        auto [a,b,c,d] = getCollisionRec(knightPos);
        DrawRectangleLines(a,b,c,d, GREEN);
    }
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{
        Vector2Subtract(worldPos, knightPos)
    };
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale};
}