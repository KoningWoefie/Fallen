#include <src/Core/scenemanager.h>

SceneManager::SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
    if(_instance == nullptr)
    {
        _instance = new SceneManager();
    }
    return _instance;
}

SceneManager::~SceneManager()
{
    for (Scene* scene : _scenes)
    {
        delete scene;
    }
}

void SceneManager::LoadScene(Scene* scene)
{
    _loadedScene = scene;
    _loadedSceneIndex = scene->thisSceneIndex;
    _loadedScene->Load();
}

void SceneManager::LoadScene(int index)
{
    try
    {
        _loadedScene = _scenes[index];
        _loadedSceneIndex = index;
        _loadedScene->Load();
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
}

void SceneManager::AddScene(Scene *scene)
{
    scene->thisSceneIndex = _scenes.size();
    _scenes.push_back(scene);
}

void SceneManager::RemoveScene(Scene *scene)
{
    for (int i = 0; i < _scenes.size(); i++)
    {
        if (_scenes[i] == scene)
        {
            delete _scenes[i];
            _scenes[i] = nullptr;
            _scenes.erase(_scenes.begin() + i);
            break;
        }
    }
}

void SceneManager::RemoveScene(int index)
{
    try
    {
        _scenes.erase(_scenes.begin() + index);
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
}

void SceneManager::RemoveAllScenes()
{
    _scenes.clear();
    _loadedScene = nullptr;
}

void SceneManager::UnloadScene()
{
    _loadedScene->Unload();
    _loadedScene = nullptr;
}

Scene* SceneManager::GetLoadedScene()
{
    if(_loadedScene == nullptr)
    {
        LoadScene(0);
    }
    return _loadedScene;
}

void SceneManager::NextScene()
{
    LoadScene(_loadedSceneIndex+1);
}

void SceneManager::PreviousScene()
{
    LoadScene(_loadedSceneIndex-1);
}

SceneManager* SceneManager::_instance = nullptr;
