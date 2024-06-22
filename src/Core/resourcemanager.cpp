#include <src/Core/resourcemanager.h>

ResourceManager::ResourceManager()
{
    std::cout << "Creating ResourceManager" << "\n";
}

ResourceManager::~ResourceManager()
{
    std::cout << "Destroying ResourceManager" << "\n";

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

    std::map<std::string, Mesh*>::iterator mesh_it;
	for (mesh_it=_meshes.begin(); mesh_it!=_meshes.end(); ++mesh_it) {
		if (mesh_it->second != nullptr) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			delete _meshes[mesh_it->first];
            _meshes[mesh_it->first] = nullptr;
		}
	}
	_meshes.clear();

    std::cout << "ResourceManager destroyed" << "\n";
}

Texture* ResourceManager::GetTexture(std::string fileName, int width, int height)
{
    if(fileName.empty())
    {
        return nullptr;
    }
    if(_textures[fileName])
    {
        return _textures[fileName];
    }
    _textures[fileName] = new Texture();
    _textures[fileName]->LoadTGA(fileName);
    return _textures[fileName];
}

Mesh* ResourceManager::GetMesh(int width, int height, int radius, glm::vec2 pivot, float uvWidth, float uvHeight, bool text, bool nineSlice)
{
    char temp[64];
    sprintf(temp, "%d_%d_%d_%.5f_%.5f", width, height, radius, pivot.x, pivot.y); //, uvWidth, uvHeight);
    std::string name(temp);
    if(_meshes[name] != nullptr)
    {
        if(_meshes[name]->UV() != glm::vec2(uvWidth, uvHeight))
        {
            delete _meshes[name];
            _meshes[name] = nullptr;
        }
        else return _meshes[name];
    }
    if(radius)
    {
        Mesh* m = new Mesh(width, height);
        m->GenerateCircleMesh(pivot, uvWidth, uvHeight, 33);
        _meshes[name] = m;
        return _meshes[name];
    }
    if(text)
    {
        Mesh* m = new Mesh(width, height);
        m->GenerateTextMesh(pivot, uvWidth, uvHeight);
        _meshes[name] = m;
        return _meshes[name];
    }
    Mesh* m = new Mesh(width, height);
    m->GenerateMesh(pivot, uvWidth, uvHeight, nineSlice);
    _meshes[name] = m;

    return _meshes[name];
}
