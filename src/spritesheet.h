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

protected:
    Timer* t;
    
    std::vector<std::vector<int>> _animations;
    float _animationDelay;

    int _currentFrame;
    int _nextFrame;
};

struct AnimatedSprite : SpriteSheet
{
    AnimatedSprite(const std::string& filePath, int spriteAmountX, int spriteAmountY, float animationDelay) : SpriteSheet(filePath, spriteAmountX, spriteAmountY)
    {
        _animationDelay = animationDelay;
    }

    virtual ~AnimatedSprite()
    {

    }

    int playAnimation(int index)
    {
        if(!t->IsStarted())
        {
            t->StartTimer();
        }
        if(t->Seconds() >= _animationDelay)
        {
            // Check if its out of range
            if(_nextFrame >= _animations[index].size())
            {
                // if it's out of range set the frame as 0 and stop the timer
                _nextFrame = 0;
                this->Frame(_animations[index][_nextFrame]);
                _nextFrame++;
                t->StopTimer();
                return 1;
            }

            // Set the next frame as the current frame
            this->Frame(_animations[index][_nextFrame]);

            // Set the next frame as the next frame
            _nextFrame++;

            // Reset timer
            t->StopTimer();
            t->StartTimer();
        }
        return 0;
    }

    void setAnimation(std::vector<int> animation) { _animations.push_back(animation); }
};


#endif