#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <cmath>
#include <chrono>
#include <iostream>
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include "WindowManagement.h"

void drawBackground(Texture2D map, Vector2 mapPosition)
{
    DrawTexture(map, mapPosition.x, mapPosition.y, WHITE);
}

void executeGameLoop(Character player, Texture2D map, Vector2 mapPosition) {
    // Game Loop
    mapPosition = Vector2Scale(player.getWorldPos(), -1.f);
    drawBackground(map, mapPosition);

    if (!player.getAlive()) {
        DrawText("Game Over!", 55.f, 45.f, 40, RED);
        EndDrawing();
        return;
    } else {
        std::string playerHealth = "Health: ";
        playerHealth.append(std::to_string(player.getHealth()), 0, 5);
        DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
    }

    // player.tick(GetFrameTime());
    // return;

    // if (
    //     player.getWorldPos().x < map.width / -2 ||
    //     player.getWorldPos().y < map.height / -4)
    //     // player.getWorldPos().x + windowWidth > map.width ||
    //     // player.getWorldPos().y + windowHeight > map.height - 10)
    // { 
    //     player.undoMovement();
    // }
}

int main()
{
    WindowManagement WindowManager;

    auto [windowWidth, windowHeight] = WindowManager.initScreen();
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPosition = {0.0, 0.0};

    Character player{
        static_cast<int>(windowWidth),
        static_cast<int>(windowHeight),
        { 0.f, 0.f}
    };

    while (!WindowShouldClose())
    {
        WindowManager.draw();

        executeGameLoop(player, map, mapPosition);
         
    player.tick(GetFrameTime());

    if (
        player.getWorldPos().x < map.width / -2 ||
        player.getWorldPos().y < map.height / -4)
        // player.getWorldPos().x + windowWidth > map.width ||
        // player.getWorldPos().y + windowHeight > map.height - 10)
    { 
        player.undoMovement();
    }

        // swap framebuffer
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}