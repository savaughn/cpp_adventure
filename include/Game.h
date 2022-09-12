#include "raylib.h"

class Game {
    public:
        bool isGameOver{
            false
        };
        void setIsGameOver(bool bGameOver) {
            isGameOver = bGameOver;
        }
        bool getIsGameOver(Character* player) {
            return !player->getAlive();
        }
        void executeGameLoop(Character* player, Texture2D map, Vector2 mapPosition, float gameTime, Game* game) {
            // Game Loop
            mapPosition = Vector2Scale(player->getWorldPos(), -1.f);
                DrawTexture(map, mapPosition.x, mapPosition.y, WHITE);

            if (game->isGameOver) {
                DrawText("Game Over!", 55.f, 45.f, 40, RED);
                EndDrawing();
                return;
            } else {
                std::string playerHealth = "Health: ";
                playerHealth.append(std::to_string(player->getHealth()), 0, 5);
                DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
            }

            player->tick(GetFrameTime());
            // return;

            if (
                    player->getWorldPos().x < map.width / -2 ||
                    player->getWorldPos().y < map.height / -4
                )
                    // player.getWorldPos().x + windowWidth > map.width ||
                    // player.getWorldPos().y + windowHeight > map.height - 10)
                { 
                    player->undoMovement();
                }
        }
};