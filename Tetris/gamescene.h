#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <src/Core/scene.h>
#include <src/UI/canvas.h>
#include <src/UI/image.h>
#include <src/UI/uielement.h>
#include <src/Objects/emptyobject.h>
#include <src/Core/config.h>

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    virtual void Update(float deltaTime);
    virtual void Initialize();

private:
    EmptyObject* _canvas;
    EmptyObject* _backgroundImage;

    void CreateGrid();

    int colNum;
    int rowNum;

    std::vector<std::vector<EmptyObject*>> _grid;
    EmptyObject* _gridObject;
};

#endif
