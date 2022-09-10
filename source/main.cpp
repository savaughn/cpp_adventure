#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <cmath>
#include <chrono>
#include <iostream>
#include "Prop.h"
#include "Enemy.h"
#include <string>

#define resolution \
    {              \
        1028, 720   \
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
        windowHeight
    };

    Enemy goblin{
        Vector2{600.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime,
    };

    for(auto enemy : enemies) {
        enemy -> setTarget(&knight);
    }

    Prop props[2]{
        Prop{
            Vector2{600.f, 450.f},
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
            prop.Render(knight.getWorldPos(), knight.isDebugActive());
        }

        if (!knight.getAlive()) {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        } else {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        if (
            knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * 3 ||
            knight.getWorldPos().y + windowHeight > map.height *3 - 10)
        { 
            // knight.undoMovement();
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

        for (auto enemy : enemies) {
            enemy->tick(GetFrameTime());
        }

        if (
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)
            ){  
            for (auto enemy : enemies) {
                if (CheckCollisionRecs(
                    knight.getWeaponCollisionRec(),
                    enemy->getCollisionRec()
                )) {
                    enemy->applyDamage(knight.getAttackPower());
                    enemy->setAlive(enemy->getHealth() > 0);
                }
            }
        }

        // swap framebuffer
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}