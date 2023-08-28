#include "SheetTest.h"

SheetTest::SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY) : SpriteSheet(filePath, spriteAmountX, spriteAmountY)
{
    _animations = 
    {
        { 0, 4, 8, 12},
        { 1, 5, 9, 13},
        { 2, 6, 10, 14},
        { 3, 7, 11, 15},
    };
    _animationDelay = 1.0f;
}

SheetTest::~SheetTest()
{

}

void SheetTest::update(float deltaTime)
{
    this->playAnimation(0);
}