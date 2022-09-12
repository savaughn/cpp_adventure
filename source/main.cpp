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

    while (!WindowShouldClose())
    {
        WindowManager.draw();
        game.executeGameLoop(&player, background.texture, background.position, GetFrameTime(), &game);
        WindowManager.endDraw();     
    }

    UnloadTexture(background.texture);
    CloseWindow();
}

#endif
