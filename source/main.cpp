#ifndef WINDOWMANAGEMENT_H
#define WINDOWMANAGEMENT_H

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <cmath>
#include <chrono>
#include <iostream>
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include "Game.h"
#include "BackgroundManager.h"

int main()
{
    WindowManagement WindowManager{"cpp_adventure"};
    BackgroundManager background{"nature_tileset/WorldMap.png"};
    Character player{WindowManager.getScreenResolution(), { 0.f, 0.f }};
    Game game;


// Camera2D, defines position/orientation in 2d space
// typedef struct Camera2D {
//     Vector2 offset;         // Camera offset (displacement from target)
//     Vector2 target;         // Camera target (rotation and zoom origin)
//     float rotation;         // Camera rotation in degrees
//     float zoom;             // Camera zoom (scaling), should be 1.0f by default
// } Camera2D;

    float width = 1920.f;
    float height = 1080.f;

    Camera2D camera = {
        { -800.f, 500.f },
        player.worldPos,
        0.f,
        1.f
    };

    while (!WindowShouldClose())
    {
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        static Vector2 bbox = { 0.2f, 0.2f };

        Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, camera);
        Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, camera);
        camera.offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

        if (player.worldPos.x < bboxWorldMin.x) camera.target.x = player.worldPos.x;
        if (player.worldPos.y < bboxWorldMin.y) camera.target.y = player.worldPos.y;
        if (player.worldPos.x > bboxWorldMax.x) camera.target.x = bboxWorldMin.x + (player.worldPos.x - bboxWorldMax.x);
        if (player.worldPos.y > bboxWorldMax.y) camera.target.y = bboxWorldMin.y + (player.worldPos.y - bboxWorldMax.y);

        WindowManager.draw(camera);
        game.executeGameLoop(&player, background.texture, background.position, GetFrameTime(), &game);
        WindowManager.endDraw();     
    }

    UnloadTexture(background.texture);
    CloseWindow();
}

#endif
