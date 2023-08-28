#include "SheetTest.h"

SheetTest::SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY, float animationDelay) : AnimatedSprite(filePath, spriteAmountX, spriteAmountY, animationDelay)
{
    this->setAnimation({0,4,8,12});
    this->setAnimation({1,5,9,13});
    this->setAnimation({2,6,10,14});
    this->setAnimation({3,7,11,15});
}

SheetTest::~SheetTest()
{

}

void SheetTest::update(float deltaTime)
{
    this->playAnimation(0);
}