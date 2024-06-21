#ifndef SHEETTEST_H
#define SHEETTEST_H

#include <src/Core/sprite.h>

class SheetTest : public SpriteSheet
{
public:
    SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY, float animationDelay);

    virtual ~SheetTest();

    virtual void update(float deltaTime);
};

#endif
