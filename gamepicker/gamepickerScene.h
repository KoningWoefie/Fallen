#ifndef GAMEPICKERSCENE_H
#define GAMEPICKERSCENE_H

#include <src/scene.h>
#include <src/sprite.h>
#include <src/text.h>
#include <src/canvas.h>
#include <src/button.h>
#include "defaultObject.h"

class GamePickerScene : public Scene
{
public:
	GamePickerScene();
    ~GamePickerScene();

    virtual void Update(float deltaTime);
private:
    void OnButtonClicked();
    void OnButtonHovered();
    void OnButtonReleased();

	DefaultObject* _canvas;

	DefaultObject* _button;
};


#endif
