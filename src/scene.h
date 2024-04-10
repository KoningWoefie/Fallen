#ifndef SCENE_H
#define SCENE_H

#include <src/object.h>
#include <src/camera.h>

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
