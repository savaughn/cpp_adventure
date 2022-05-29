#include "raylib.h"
#include "raymath.h"
#define resolution \
    {              \
        384, 384   \
    }
#include <cmath>
#include <chrono>
#include <iostream>

using namespace std::chrono;

struct screenResolution
{
    int width;
    int height;
};

struct AnimData
{
    int frame;
    float runningTime;
    const float updateTime;
    const int maxFrame;
};

Vector2 initScreen()
{
    const auto [windowWidth, windowHeight] = screenResolution resolution;
    InitWindow(windowWidth, windowHeight, "Cpp Adventure");
    SetTargetFPS(60);
    return {(float)windowWidth, (float)windowHeight};
}

void drawBackground(Texture2D map, Vector2 mapPosition)
{
    DrawTexture(map, mapPosition.x, mapPosition.y, WHITE);
}

class Character
{
public:
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void drawPlayer(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    AnimData animData{
        0,
        0.0f,
        1.f / 12.f,
        6};
    const float speed{4.f};
};

void Character::drawPlayer(Texture2D knight, Vector2 knightPosition, Vector2 direction, float rightLeft, AnimData animData)
{
    rightLeft = direction.x < 0.f ? -1.f : 1.f;
    Rectangle sourceRectangle = {animData.frame * (float)knight.width / 6.f, 0.f, (rightLeft) * (float)knight.width / 6.f, (float)knight.height};
    Rectangle destinationRectangle = {knightPosition.x, knightPosition.y, 4.0f * (float)knight.width / 6.f, 4.0f * (float)knight.height};
    DrawTexturePro(knight, sourceRectangle, destinationRectangle, {0, 0}, 0.f, WHITE);
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
};

void Character::tick(float deltaTime)
{
    Vector2 direction{0.f, 0.f};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
    }

    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateTime)
    {
        animData.frame += 1 % animData.maxFrame;
        animData.runningTime = 0;
    }
    texture = Vector2Length(direction) ? run : idle;

    drawPlayer(texture, screenPos, direction, 1.f, animData);
}

int main()
{

    Vector2 window = initScreen();
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPosition = {0.0, 0.0};

    Character knight{};
    knight.setScreenPos(window.x, window.y);

    while (!WindowShouldClose())
    {

        // Init framebuffer
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Game Loop
        mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);
        drawBackground(map, mapPosition);
        knight.tick(GetFrameTime());

        // swap framebuffer
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}