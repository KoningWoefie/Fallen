#include "SheetTest.h"

SheetTest::SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY, float animationDelay) : SpriteSheet(filePath, spriteAmountX, spriteAmountY)
{
    // this->SetAnimation({0,4,8,12});
    // this->SetAnimation({1,5,9,13});
    // this->SetAnimation({2,6,10,14});
    // this->SetAnimation({3,7,11,15});
}

SheetTest::~SheetTest()
{

}

void SheetTest::update(float deltaTime)
{
    // this->PlayAnimation(0);
}
