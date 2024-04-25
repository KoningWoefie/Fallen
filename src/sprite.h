#ifndef SPRITE_H
#define SPRITE_H

#include <src/component.h>
#include <vector>

class Sprite
{
public:
    // Constructor
    // parameter filepath for the texture this is only compatible with .tga files at the moment
    Sprite(const std::string& filePath);

    // Destructor
    virtual ~Sprite();

    std::string FileName() { return m_filename; }

    glm::vec2 UV;

    int Type() { return _type; }
private:
    std::string m_filename;

protected:
    int _type;

};

struct meshData
{
    float uvWidth;
    float uvHeight;
    float uvOffsetX;
    float uvOffsetY;
    glm::vec2 pivot;
    int width;
    int height;
    bool corner;
    int radius;
};

class SlicedSprite : public Sprite
{
public:
    // Constructor (if width and height are 0, the sprite will be the size of the texture)
    SlicedSprite(const std::string& filePath, int left, int right, int top, int bottom, int width = 0, int height = 0);

    // Destructor
    virtual ~SlicedSprite();

    // This is for the renderer so that the sprite knows of the size of the texture
    void ChangeMeshData(int width, int height);

    std::vector<meshData> GetMeshData() { return _meshData; }
private:

    int _left;
    int _right;
    int _top;
    int _bottom;

    // If the meshData has changed you should not change it again
    bool changed;

    // Store the mesh data for each of the nine slices
    std::vector<meshData> _meshData;

    void GenerateMeshData(int ileft, int iright, int itop, int ibottom, int width, int height);
};

class SpriteSheet : public Sprite
{
public:
    SpriteSheet(const std::string& filePath);
    SpriteSheet(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical);
    SpriteSheet(const std::string& filePath, int spriteAmountHorizontal, int spriteAmountVertical, int width, int height);

    virtual ~SpriteSheet();

    int GetCurrentFrame() { return _currentFrame; }
    void SetCurrentFrame(int f);

    void SetWidth(int width) { _width = width; }
    void SetHeight(int height) { _height = height; }

    int GetSpriteWidth() { return _width; }
    int GetSpriteHeight() { return _height; }

    glm::vec2 GetUVOffset() { return _uvOffset; }

    float GetUVWidth() { return _uvWidth; }
    float GetUVHeight() { return _uvHeight; }

private:
    int _spriteAmountHorizontal;
    int _spriteAmountVertical;
    int _currentFrame;
    int _width;
    int _height;

    float _uvWidth;
    float _uvHeight;

    glm::vec2 _uvOffset;
};

#endif
