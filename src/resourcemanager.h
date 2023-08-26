#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <src/texture.h>
#include <src/mesh.h>

class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();

    Texture* GetTexture(std::string fileName, int width = 0, int height = 0);
    Mesh* GetMesh(int width, int height, int radius, float uvWidth = 1.0f, float uvHeight = 1.0f);
private:
    std::map<std::string, Texture*> _textures;
    std::map<std::string, Mesh*> _meshes;
};

#endif