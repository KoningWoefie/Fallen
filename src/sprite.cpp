#include <src/sprite.h>

Sprite::Sprite(const std::string& filePath)
{
    _type = 0;
    m_filename = filePath;
}

Sprite::~Sprite()
{
}

SlicedSprite::SlicedSprite(const std::string& filePath, int ileft, int iright, int itop, int ibottom, int width, int height) : Sprite(filePath)
{
    _type = 1;
    changed = false;
    GenerateMeshData(ileft, iright, itop, ibottom, width, height);
}

SlicedSprite::~SlicedSprite()
{
    _meshData.clear();
}

void SlicedSprite::GenerateMeshData(int ileft, int iright, int itop, int ibottom, int width, int height)
{
    _left = ileft;
    _right = iright;
    _top = itop;
    _bottom = ibottom;

    // Create the mesh data for the nine slices
    meshData topLeft;
    meshData top;
    meshData topRight;
    meshData left;
    meshData center;
    meshData right;
    meshData bottomLeft;
    meshData bottom;
    meshData bottomRight;

    // Set the mesh data for the nine slices
    topLeft.uvWidth = (float)ileft / (float)width;
    topLeft.uvHeight = (float)itop / (float)height;
    topLeft.uvOffsetX = 0.0f;
    topLeft.uvOffsetY = (float)(height - itop) / (float)height;
    topLeft.pivot = glm::vec2(0.5f, 0.5f);
    topLeft.width = ileft;
    topLeft.height = itop;
    topLeft.corner = true;
    topLeft.radius = 0;

    top.uvWidth = (float)(width - iright - ileft) / (float)width;
    top.uvHeight = (float)itop / (float)height;
    top.uvOffsetX = (float)ileft / (float)width;
    top.uvOffsetY = (float)(height - itop) / (float)height;
    top.pivot = glm::vec2(0.5f, 0.5f);
    top.width = width - ileft - iright;
    top.height = itop;
    top.corner = false;
    top.radius = 0;

    topRight.uvWidth = (float)iright / (float)width;
    topRight.uvHeight = (float)itop / (float)height;
    topRight.uvOffsetX = (float)(width - iright) / (float)width;
    topRight.uvOffsetY = (float)(height - itop) / (float)height;
    topRight.pivot = glm::vec2(0.5f, 0.5f);
    topRight.width = iright;
    topRight.height = itop;
    topRight.corner = true;
    topRight.radius = 0;

    left.uvWidth = (float)ileft / (float)width;
    left.uvHeight = (float)(height - ibottom - itop) / (float)height;
    left.uvOffsetX = 0.0f;
    left.uvOffsetY = (float)itop / (float)height;
    left.pivot = glm::vec2(0.5f, 0.5f);
    left.width = ileft;
    left.height = height - itop - ibottom;
    left.corner = false;
    left.radius = 0;

    center.uvWidth = (float)(width - iright - ileft) / (float)width;
    center.uvHeight = (float)(height - ibottom - itop) / (float)height;
    center.uvOffsetX = (float)ileft / (float)width;
    center.uvOffsetY = (float)itop / (float)height;
    center.pivot = glm::vec2(0.5f, 0.5f);
    center.width = width - ileft - iright;
    center.height = height - itop - ibottom;
    center.corner = false;
    center.radius = 0;

    right.uvWidth = (float)iright / (float)width;
    right.uvHeight = (float)(height - ibottom - itop) / (float)height;
    right.uvOffsetX = (float)(width - iright) / (float)width;
    right.uvOffsetY = (float)itop / (float)height;
    right.pivot = glm::vec2(0.5f, 0.5f);
    right.width = iright;
    right.height = height - itop - ibottom;
    right.corner = false;
    right.radius = 0;

    bottomLeft.uvWidth = (float)ileft / (float)width;
    bottomLeft.uvHeight = (float)ibottom / (float)height;
    bottomLeft.uvOffsetX = 0.0f;
    bottomLeft.uvOffsetY = 0.0f;
    bottomLeft.pivot = glm::vec2(0.5f, 0.5f);
    bottomLeft.width = ileft;
    bottomLeft.height = ibottom;
    bottomLeft.corner = true;
    bottomLeft.radius = 0;

    bottom.uvWidth = (float)(width - iright - ileft) / (float)width;
    bottom.uvHeight = (float)ibottom / (float)height;
    bottom.uvOffsetX = (float)ileft / (float)width;
    bottom.uvOffsetY = 0.0f;
    bottom.pivot = glm::vec2(0.5f, 0.5f);
    bottom.width = width - ileft - iright;
    bottom.height = ibottom;
    bottom.corner = false;
    bottom.radius = 0;

    bottomRight.uvWidth = (float)iright / (float)width;
    bottomRight.uvHeight = (float)ibottom / (float)height;
    bottomRight.uvOffsetX = (float)(width - iright) / (float)width;
    bottomRight.uvOffsetY = 0.0f;
    bottomRight.pivot = glm::vec2(0.5f, 0.5f);
    bottomRight.width = iright;
    bottomRight.height = ibottom;
    bottomRight.corner = true;
    bottomRight.radius = 0;

    _meshData.push_back(center);
    _meshData.push_back(left);
    _meshData.push_back(right);
    _meshData.push_back(top);
    _meshData.push_back(bottom);
    _meshData.push_back(topLeft);
    _meshData.push_back(topRight);
    _meshData.push_back(bottomLeft);
    _meshData.push_back(bottomRight);
}

void SlicedSprite::ChangeMeshData(int width, int height)
{
    if(changed) return;
    _meshData.clear();
    GenerateMeshData(_left, _right, _top, _bottom, width, height);
    changed = true;
}

SpriteSheet::SpriteSheet(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical) : Sprite(filePath)
{
    _type = 2;
    _currentFrame = 0;

    _spriteAmountHorizontal = spriteAmountHorizontal;
    _spriteAmountVertical = spriteAmountVertical;
    _width = 0;
    _height = 0;

    _uvWidth = 1.0f / spriteAmountHorizontal;
    _uvHeight = 1.0f / spriteAmountVertical;

	_uvOffset = glm::vec2(0.0f, 0.0f);
}

SpriteSheet::SpriteSheet(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical, int width, int height) : Sprite(filePath)
{
    _type = 2;
    _currentFrame = 0;

    _spriteAmountHorizontal = spriteAmountHorizontal;
    _spriteAmountVertical = spriteAmountVertical;

    _width = width;
    _height = height;

    _uvWidth = 1.0f / spriteAmountHorizontal;
    _uvHeight = 1.0f / spriteAmountVertical;

	_uvOffset = glm::vec2(0.0f, 0.0f);
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetCurrentFrame(int f)
{
    if(f > _spriteAmountHorizontal * _spriteAmountVertical || f < 0) return;

    int xPos = f % _spriteAmountHorizontal;
    int yPos = f / _spriteAmountHorizontal;

    _uvOffset.x = xPos * _uvWidth;
    _uvOffset.y = yPos * _uvHeight;

    _currentFrame = f;
}

AnimatedSprite::AnimatedSprite(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical, float timePerFrame) : SpriteSheet(filePath, spriteAmountHorizontal, spriteAmountVertical)
{
    _type = 3;
    _timePerFrame = timePerFrame;
	_currentAnimation = 0;
    _timer = new Timer();
}

AnimatedSprite::AnimatedSprite(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical, float timePerFrame, int width, int height) : SpriteSheet(filePath, spriteAmountHorizontal, spriteAmountVertical, width, height)
{
    _type = 3;
    _timePerFrame = timePerFrame;
	_currentAnimation = 0;
    _timer = new Timer();
}

AnimatedSprite::~AnimatedSprite()
{
    _animations.clear();
    delete _timer;
    _timer = nullptr;
}

void AnimatedSprite::AddAnimation(std::vector<int> animation)
{
    if(!GetAnimation(animation).empty()) return;
    _animations.push_back(animation);
}

void AnimatedSprite::RemoveAnimation(int animationIndex)
{
    if(animationIndex < 0 || animationIndex >= _animations.size()) return;
    _animations.erase(_animations.begin() + animationIndex);
}

void AnimatedSprite::RemoveAnimation(std::vector<int> animation)
{
    for(int i = 0; i < _animations.size(); i++)
    {
        for(int j = 0; j < _animations[i].size(); j++)
        {
            if(_animations[i][j] != animation[j]) break;
            if(j == _animations[i].size() - 1)
            {
                _animations.erase(_animations.begin() + i);
                return;
            }
        }
    }
}

void AnimatedSprite::RemoveAllAnimations()
{
    _animations.clear();
}

std::vector<int> AnimatedSprite::GetAnimation(int animationIndex)
{
    if(animationIndex < 0 || animationIndex >= _animations.size()) return std::vector<int>();
    return _animations[animationIndex];
}

std::vector<int> AnimatedSprite::GetAnimation(std::vector<int> animation)
{
    for(int i = 0; i < _animations.size(); i++)
    {
        for(int j = 0; j < _animations[i].size(); j++)
        {
            if(_animations[i][j] != animation[j]) break;
            if(j == _animations[i].size() - 1) return _animations[i];
        }
    }
    return std::vector<int>();
}

void AnimatedSprite::SetAnimation(int animationIndex)
{
    _currentAnimation = animationIndex;
    _currentFrame = 0;
    _timer->StopTimer();
    _timer->StartTimer();
}

void AnimatedSprite::SetAnimation(std::vector<int> animation)
{
    for(int i = 0; i < _animations.size(); i++)
    {
        for(int j = 0; j < _animations[i].size(); j++)
        {
            if(_animations[i][j] != animation[j]) break;
            if(j == _animations[i].size() - 1)
            {
                _currentAnimation = i;
                _currentFrame = 0;
                return;
            }
        }
    }
}

void AnimatedSprite::Update()
{
    if(_animations.empty()) return;
    if(!_timer->IsStarted()) _timer->StartTimer();
    if(_timer->Seconds() >= _timePerFrame)
    {
        _timer->StopTimer();
        _timer->StartTimer();
        _currentFrame++;
        if(_currentFrame >= _animations[_currentAnimation].size()) _currentFrame = 0;
        SetCurrentFrame(_currentFrame);
    }
}
