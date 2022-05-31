#include "BaseCharacter.h"

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
        screenPos.x + (width * scale * (0.5f)/2.f),
        screenPos.y + height * scale * 0.75f,
        width * scale * 0.5f,
        height * scale / 8.f
    };
}