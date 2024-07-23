#ifndef CARDSCENE_H
#define CARDSCENE_H

#include <src/Core/scene.h>
#include "CardGame/card.h"
#include "CardGame/deck.h"
#include "CardGame/hand.h"
#include <src/Presets/emptyobject.h>
#include <src/Presets/inputfield.h>

class CardScene : public Scene
{
public:
    CardScene();
    virtual ~CardScene();

    virtual void Initialize();

    virtual void Update(float deltaTime);

private:
    Hand* _hand;
    Presets::InputField* _inputField;
    Presets::EmptyObject* _titleText;
};

#endif
