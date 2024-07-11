#include <src/Core/config.h>

int Config::ScreenWidth = 1280;
int Config::ScreenHeight = 720;

std::string Config::Title = "DefaultGameTitle";
int Config::Screenmode = (int)ScreenMode::Windowed;

bool Config::ChangedScreenMode = false;
bool Config::ChangedTitle = false;
bool Config::ChangedColor = false;

glm::vec3 Config::BackgroundColor = glm::vec3(150.0f, 150.0f, 150.0f);

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

void Config::SetBackgroundColor(glm::vec3 color)
{
    Config::BackgroundColor = color;
    Config::ChangedColor = true;
}
