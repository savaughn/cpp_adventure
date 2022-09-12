#include "raylib.h"
#include <string>

struct Background {
    Texture2D texture;
    Vector2 position;
};

class BackgroundManager {
    public:
        BackgroundManager(const char* bgAsset, Vector2 initialPosition = {}) {
            texture = LoadTexture(bgAsset);
            position = initialPosition;
        }
        Texture2D texture;
        Vector2 position;
};