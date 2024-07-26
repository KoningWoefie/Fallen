#ifndef HOMESCENE_H
#define HOMESCENE_H

#include <src/Core/scene.h>
#include <src/Objects/emptyobject.h>
#include <src/UI/image.h>
#include <src/Core/text.h>
#include <src/UI/canvas.h>
#include <src/Objects/button.h>

class HomeScene : public Scene
{
public:
    HomeScene();
    virtual ~HomeScene();

    virtual void Initialize();

    virtual void Update(float deltaTime);
private:
    void StartGame();
    EmptyObject* _titleImage;
    EmptyObject* _startButton;
    EmptyObject* _text;
    std::vector<Button*> _columns;
    EmptyObject* _canvas;
};

#endif
