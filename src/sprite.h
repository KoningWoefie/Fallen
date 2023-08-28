#ifndef SPRITE_H
#define SPRITE_H

#include <src/dynamic.h>

class Sprite : public Dynamic
{
public:
    // Constructor
    // parameter filepath for the texture this must be a .tga at the moment
    Sprite(const std::string& filePath);

    // Destructor
    virtual ~Sprite();

    virtual void update(float deltaTime);
private:
};


#endif