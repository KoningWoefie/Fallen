#include <src/spritesheet.h>

// Call the base contructor and give the parameter filepath to that base constructor
SpriteSheet::SpriteSheet(const std::string& filePath, int spriteAmountX, int spriteAmountY) : Sprite(filePath)
{
    _uvWidth = 1.0f / (float)spriteAmountX;
    _uvHeight = 1.0f / (float)spriteAmountY;

    _currentFrame = 0;
    _nextFrame = 0;

    t = new Timer();
    t->StartTimer();
};

SpriteSheet::~SpriteSheet()
{
}

int SpriteSheet::Frame(int f)
{
    // How many sprites are in the width
    int w = 1.0f / _uvWidth;

    // How many sprites are in the height
    int h = 1.0f / _uvHeight;

    // If the frame is either too small or too big, say its out of range and return
    if (f >= w * h || f < 0) { std::cout << "this is a frame outside of your spritesheet" << std::endl; return -1; };

    // The position of the given frame
    int xPos = f % w;
    int yPos = f / w;

    // Set the offset of the spritesheet so it displays the correct frame
    _uvOffset[0] = xPos * _uvWidth;
    _uvOffset[1] = yPos * _uvHeight;

    _currentFrame = f;

    // Return the frame you have just set
    return _currentFrame;
}