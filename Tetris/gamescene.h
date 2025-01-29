#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <src/Core/scene.h>

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    virtual void Update(float deltaTime);
    virtual void Initialize();
};

#endif
