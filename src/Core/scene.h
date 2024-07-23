#ifndef SCENE_H
#define SCENE_H

#include <src/Core/object.h>
#include <src/Core/camera.h>

class Scene : public Object
{
public:
    Scene();
    virtual ~Scene();

    virtual void Update(float deltaTime) = 0;

    Camera* GetCamera() { return _camera; }
protected:
    virtual void Initialize() = 0;
    int ThisSceneIndex() { return thisSceneIndex; }
private:
    Camera* _camera;

    int thisSceneIndex;
    void Load();
    void Unload();
    friend class SceneManager;
};

#endif
