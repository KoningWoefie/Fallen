#include <src/uisprite.h>

UISprite::UISprite(const std::string& filePath, int ileft, int iright, int itop, int ibottom, int width, int height) : Sprite(filePath)
{
    _type = 1;
    changed = false;
    generateMeshData(ileft, iright, itop, ibottom, width, height);
}

UISprite::~UISprite()
{
    _meshData.clear();
}

void UISprite::update(float deltaTime)
{

}

void UISprite::generateMeshData(int ileft, int iright, int itop, int ibottom, int width, int height)
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
    topLeft.uvOffsetY = 0.0f;
    topLeft.pivot = glm::vec2(0.5f, 0.5f);
    topLeft.width = ileft;
    topLeft.height = itop;
    topLeft.corner = true;
    topLeft.radius = 0;

    top.uvWidth = (float)(width - iright - ileft) / (float)width;
    top.uvHeight = (float)itop / (float)height;
    top.uvOffsetX = (float)ileft / (float)width;
    top.uvOffsetY = 0.0f;
    top.pivot = glm::vec2(0.5f, 0.5f);
    top.width = width - ileft - iright;
    top.height = itop;
    top.corner = false;
    top.radius = 0;

    topRight.uvWidth = (float)iright / (float)width;
    topRight.uvHeight = (float)itop / (float)height;
    topRight.uvOffsetX = (float)(width - iright) / (float)width;
    topRight.uvOffsetY = 0.0f;
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
    bottomLeft.uvOffsetY = (float)(height - ibottom) / (float)height;
    bottomLeft.pivot = glm::vec2(0.5f, 0.5f);
    bottomLeft.width = ileft;
    bottomLeft.height = ibottom;
    bottomLeft.corner = true;
    bottomLeft.radius = 0;

    bottom.uvWidth = (float)(width - iright - ileft) / (float)width;
    bottom.uvHeight = (float)ibottom / (float)height;
    bottom.uvOffsetX = (float)ileft / (float)width;
    bottom.uvOffsetY = (float)(height - ibottom) / (float)height;
    bottom.pivot = glm::vec2(0.5f, 0.5f);
    bottom.width = width - ileft - iright;
    bottom.height = ibottom;
    bottom.corner = false;
    bottom.radius = 0;

    bottomRight.uvWidth = (float)iright / (float)width;
    bottomRight.uvHeight = (float)ibottom / (float)height;
    bottomRight.uvOffsetX = (float)(width - iright) / (float)width;
    bottomRight.uvOffsetY = (float)(height - ibottom) / (float)height;
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

void UISprite::changeMeshData(int width, int height)
{
    if(changed) return;
    _meshData.clear();
    generateMeshData(_left, _right, _top, _bottom, width, height);
    changed = true;
}
