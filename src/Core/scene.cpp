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

void Scene::Load()
{
    Initialize();
}

void Scene::Unload()
{
    for (Object* o : this->GetChildren())
    {
        delete o;
        o = nullptr;
    }
}
