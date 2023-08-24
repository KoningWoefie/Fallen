#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <src/texture.h>

class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();

    Texture* GetTexture(std::string& fileName, int width = 0, int height = 0);
private:
    std::map<std::string, Texture*> _textures;
};

#endif