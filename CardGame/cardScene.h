#ifndef CARDSCENE_H
#define CARDSCENE_H

#include <src/Core/scene.h>

class CardScene : public Scene
{
public:
    CardScene();
    virtual ~CardScene();

    virtual void Update(float deltaTime);

private:
};

#endif
