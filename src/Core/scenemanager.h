#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <src/Core/scene.h>

class SceneManager
{
public:
    static SceneManager* GetInstance();

    virtual ~SceneManager();
    void LoadScene(Scene* scene);
    void LoadScene(int index);

    void AddScene(Scene* scene);

    void RemoveScene(int index);
    void RemoveScene(Scene* scene);
    void RemoveAllScenes();

    void NextScene();
    void PreviousScene();

    Scene* GetLoadedScene();
private:
    SceneManager();
    static SceneManager* _instance;
    void UnloadScene();
    Scene* _loadedScene;
    int _loadedSceneIndex;
    std::vector<Scene*> _scenes;
};

#endif
