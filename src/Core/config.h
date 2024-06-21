#ifndef CONFIG_H
#define CONFIG_H

#define PI 3.14159265359

#include <string>

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
    static std::string Title;

    static void SetScreenMode(ScreenMode mode);
    static int GetScreenMode() { return Screenmode; };
private:
    static int Screenmode;
    static bool ChangedScreenMode;
    friend class Game;
};


#endif // CONFIG_H
