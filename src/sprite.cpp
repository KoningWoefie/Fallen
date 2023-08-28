#include <src/sprite.h>

Sprite::Sprite(const std::string& filePath)
{
    _texturePath = filePath;
}

Sprite::~Sprite()
{
}

void Sprite::update(float deltaTime)
{
}