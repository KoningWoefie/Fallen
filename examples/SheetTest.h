#ifndef SHEETTEST_H
#define SHEETTEST_H

#include <src/spritesheet.h>

class SheetTest : public AnimatedSprite
{
public:
    SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY, float animationDelay);

    virtual ~SheetTest();

    virtual void update(float deltaTime);
};

#endif