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
private:
    Camera* _camera;
};

#endif
