#ifndef CARDSCENE_H
#define CARDSCENE_H

#include <src/Core/scene.h>
#include "CardGame/card.h"
#include "CardGame/deck.h"
#include "CardGame/hand.h"
#include <src/Objects/emptyobject.h>
#include <src/Objects/inputfield.h>

class CardScene : public Scene
{
public:
    CardScene();
    virtual ~CardScene();

    virtual void Initialize();

    virtual void Update(float deltaTime);

private:
    Hand* _hand;
    InputField* _inputField;
    EmptyObject* _titleText;
};

#endif
