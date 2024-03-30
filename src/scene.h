#ifndef SCENE_H
#define SCENE_H

#include <src/dynamic.h>
#include <src/camera.h>

class Scene : public Dynamic
{
public:
    Scene();
    virtual ~Scene();

    virtual void update(float deltaTime) = 0;

    Camera* camera() { return _camera; }
private:
    Camera* _camera;
};

#endif
