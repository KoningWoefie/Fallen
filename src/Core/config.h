#ifndef CONFIG_H
#define CONFIG_H

#define PI 3.14159265359

#include <string>
#include <glm/glm.hpp>

enum class ScreenMode
{
    Windowed,
    Fullscreen
};

class Config
{
public:
    static int ScreenWidth;
    static int ScreenHeight;

    static void SetScreenMode(ScreenMode mode);
    static int GetScreenMode() { return Screenmode; };

    static void SetTitle(std::string title);
    static std::string GetTitle() { return Title; };

    static glm::vec3 GetBackgroundColor() { return BackgroundColor; };
    static void SetBackgroundColor(glm::vec3 color);

private:
    static std::string Title;
    static glm::vec3 BackgroundColor;
    static int Screenmode;

    static bool ChangedScreenMode;
    static bool ChangedTitle;
    static bool ChangedColor;
    friend class Game;
};


#endif // CONFIG_H
