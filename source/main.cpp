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
#include "InputHandler.h"
#include "TestScene.h"

int main()
{
    WindowManagement WindowManager{"cpp_adventure"};
    BackgroundManager background{"nature_tileset/WorldMap.png"};
    // Character player{WindowManager.getScreenResolution(), { 0.f, 0.f }};
    
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

    // Camera2D camera = {
    //     { -800.f, 500.f },
    //     player.worldPos,
    //     0.f,
    //     1.f
    // };

    while (!WindowShouldClose())
    {

        InputHandler inputHandler;

        std::shared_ptr<Scene> currentScene = std::make_shared<TestScene>();
        currentScene->loadResources();

		SetTargetFPS(60);
		

		// Main game loop
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			// Update
			inputHandler.handleInput(*currentScene);
			auto nextScene = currentScene->update();
			if(nextScene) {
				nextScene->loadResources();
				currentScene = nextScene;
			}
			
			// Draw
			BeginDrawing();
			currentScene->draw();
			EndDrawing();
		}
    }

    UnloadTexture(background.texture);
    CloseWindow();
}
