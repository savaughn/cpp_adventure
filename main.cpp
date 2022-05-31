#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <cmath>
#include <chrono>
#include <iostream>
#include "Prop.h"
#include "Enemy.h"
#define resolution \
    {              \
        384, 384   \
    }

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

    auto [windowWidth, windowHeight] = initScreen();
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPosition = {0.0, 0.0};

    Character knight{
        windowWidth,
        windowHeight};

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Prop props[2]{
        Prop{
            Vector2{600.f, 300.f},
            LoadTexture("nature_tileset/Rock.png")},
        Prop{
            Vector2{400.f, 500.f},
            LoadTexture("nature_tileset/Log.png")},
    };

    while (!WindowShouldClose())
    {

        // Init framebuffer
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Game Loop
        mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);
        drawBackground(map, mapPosition);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        if (
            knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width ||
            knight.getWorldPos().y + windowHeight > map.height - 10)
        { 
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if(CheckCollisionRecs(
                prop.getCollisionRec(
                    knight.getWorldPos()
                ),
                knight.getCollisionRec()
            )) {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        // swap framebuffer
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}