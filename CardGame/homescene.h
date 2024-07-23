#ifndef HOMESCENE_H
#define HOMESCENE_H

#include <src/Core/scene.h>
#include <src/Presets/emptyobject.h>
#include <src/Presets/canvas.h>
#include <src/UI/image.h>
#include <src/UI/button.h>
#include <src/Core/text.h>

class HomeScene : public Scene
{
public:
    HomeScene();
    virtual ~HomeScene();

    virtual void Initialize();

    virtual void Update(float deltaTime);
private:
    void StartGame();
    Presets::EmptyObject* _titleImage;
    Presets::EmptyObject* _startButton;
    Presets::EmptyObject* _text;
    Presets::Canvas* _canvas;
};

#endif
