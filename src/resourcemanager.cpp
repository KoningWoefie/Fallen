#include <src/resourcemanager.h>

ResourceManager::ResourceManager()
{
    std::cout << "Creating ResourceManager" << std::endl;
}

ResourceManager::~ResourceManager()
{
    std::cout << "Destroying ResourceManager" << std::endl;

    //delete all the textures in the map
    std::map<std::string, Texture*>::iterator text_it;
	for (text_it=_textures.begin(); text_it!=_textures.end(); ++text_it) {
		if (text_it->second != nullptr) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			delete _textures[text_it->first];
            _textures[text_it->first] = nullptr;
		}
	}
	_textures.clear();

    std::cout << "ResourceManager destroyed" << std::endl;
}

Texture* ResourceManager::GetTexture(std::string& fileName, int width, int height)
{
    if(fileName.empty())
    {
        char temp[32];
        sprintf(temp, "%d_%d", width, height);
        std::string name(temp);
        fileName = name;
    }

    if(_textures[fileName])
    {
        return _textures[fileName];
    }
    if(width || height)
    {
        _textures[fileName] = new Texture(width, height);
        return _textures[fileName];
    }
    _textures[fileName] = new Texture();
    _textures[fileName]->loadTGA(fileName);
    return _textures[fileName];
}