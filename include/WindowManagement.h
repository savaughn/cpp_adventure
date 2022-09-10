#include "raylib.h"
#include <map>
#define GameResolution \
    {              \
        1920, 1080   \
    }
#define screenSize  \
    {               \
        GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()) \
    }

struct screenResolution
{
    int width;
    int height;
};


class WindowManagement {
    public:
        Vector2 initScreen()
        {
            const auto [windowWidth, windowHeight] = screenResolution GameResolution;
            InitWindow(windowWidth, windowHeight, "Cpp Adventure");
            SetTargetFPS(60);
            return {static_cast<float>(windowWidth), static_cast<float>(windowHeight)};
        }
        void handleFullscreenToggle() {
            if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
            {
                std::map<bool, screenResolution>resolutions = {
                    { true, GameResolution },
                    { false, screenSize }
                };
                
                bool isFullScreen = IsWindowFullscreen();
                SetWindowSize(static_cast<int>(resolutions[isFullScreen].width), static_cast<int>(resolutions[isFullScreen].height));
                // toggle the state
                ToggleFullscreen();
            }
        }
        void draw() {
            handleFullscreenToggle();
            // Init framebuffer
            BeginDrawing();
            ClearBackground(RAYWHITE);
        }

};

