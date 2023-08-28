#ifndef SHEETTEST_H
#define SHEETTEST_H

#include <src/spritesheet.h>

class SheetTest : public SpriteSheet
{
public:
    SheetTest(const std::string& filePath, int spriteAmountX, int spriteAmountY);

    virtual ~SheetTest();

    virtual void update(float deltaTime);
};

#endif