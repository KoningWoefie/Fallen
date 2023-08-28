#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <src/sprite.h>
#include <src/timer.h>

class SpriteSheet : public Sprite
{
public:
    // Constructor
    SpriteSheet(const std::string& filePath, int spriteAmountX, int spriteAmountY);

    // Destructor
    virtual ~SpriteSheet();

    // Update function
    virtual void update(float deltaTime) = 0;

    // Set the frame of the spritesheet you want to use
    int Frame(int f);

    int playAnimation(int index);
private:
    int _currentFrame;
    int _nextFrame;
    Timer* t;

protected:
    // Set this in a derived class
    std::vector<std::vector<int>> _animations;
    float _animationDelay;
};

#endif