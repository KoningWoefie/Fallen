#include <src/Core/config.h>

int Config::ScreenWidth = 1280;
int Config::ScreenHeight = 720;

std::string Config::Title = "DefaultGameTitle";
int Config::Screenmode = (int)ScreenMode::Windowed;

bool Config::ChangedScreenMode = false;
bool Config::ChangedTitle = false;

void Config::SetScreenMode(ScreenMode mode)
{
    Config::Screenmode = (int)mode;
    Config::ChangedScreenMode = true;
}

void Config::SetTitle(std::string title)
{
    Config::Title = title;
    Config::ChangedTitle = true;
}
