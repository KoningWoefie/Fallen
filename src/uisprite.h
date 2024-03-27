#ifndef UISPRITE_H
#define UISPRITE_H

#include <src/sprite.h>

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

class UISprite : public Sprite
{
public:
    // Constructor (if width and height are 0, the sprite will be the size of the texture)
    UISprite(const std::string& filePath, int left, int right, int top, int bottom, int width = 0, int height = 0);

    // Destructor
    virtual ~UISprite();

    virtual void update(float deltaTime);

    void changeMeshData(int width, int height);
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
    
    void generateMeshData(int ileft, int iright, int itop, int ibottom, int width, int height);
};

#endif