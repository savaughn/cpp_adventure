#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <cmath>
#include <chrono>
#include <iostream>
#define resolution {384, 384}

struct screenResolution
{
    int width;
    int height;
};

Vector2 initScreen()
{
    const auto [windowWidth, windowHeight] = screenResolution resolution;
    InitWindow(windowWidth, windowHeight, "Cpp Adventure");
    SetTargetFPS(60);
    return {static_cast<float>(windowWidth), static_cast<float>(windowHeight)};
}

void drawBackground(Texture2D map, Vector2 mapPosition)
{
    DrawTexture(map, mapPosition.x, mapPosition.y, WHITE);
}

int main()
{

    auto [ windowWidth, windowHeight ] = initScreen();
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPosition = {0.0, 0.0};
    const float mapScale = 4.f;

    Character knight{
        windowWidth,
        windowHeight
    };

    while (!WindowShouldClose())
    {

        // Init framebuffer
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Game Loop
        mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);
        drawBackground(map, mapPosition);
        knight.tick(GetFrameTime());

        if (
            knight.getWorldPos().x < 0.f - 5 ||
            knight.getWorldPos().y < 0.f - 5 ||
            knight.getWorldPos().x + window.x > map.width ||
            knight.getWorldPos().y + window.y > map.height        
        ) {
            knight.undoMovement();
        }

        // swap framebuffer
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}