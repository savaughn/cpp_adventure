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
#define fpsTarget 60

struct screenResolution
{
    int width;
    int height;
};


class WindowManagement {
    public:
        WindowManagement(const char* windowTitle) {
            const auto [windowWidth, windowHeight] = screenResolution GameResolution;
            InitWindow(windowWidth, windowHeight, windowTitle);
            SetTargetFPS(fpsTarget);
            screenRes = { windowWidth, windowHeight };
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
        void draw(Camera2D camera) {
            handleFullscreenToggle();
            // Init framebuffer
            BeginDrawing();
            BeginMode2D(camera);
            ClearBackground(RAYWHITE);
        }

        void endDraw() {
            EndMode2D();
            // swap framebuffer
            EndDrawing();
        }
        screenResolution getScreenResolution() {
            return screenSize;
        }

    protected:
        screenResolution screenRes;

};

