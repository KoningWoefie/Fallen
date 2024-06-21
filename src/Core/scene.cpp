#include <src/Core/scene.h>

Scene::Scene()
{
    _camera = new Camera();
}

Scene::~Scene()
{
    delete _camera;
    _camera = nullptr;
}
