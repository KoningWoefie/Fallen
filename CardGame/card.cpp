#include "CardGame/card.h"

Card::Card(int value, CardType type)
{
    FallenUI::Image* image = new FallenUI::Image();
    image->width = 500;
    image->height = 700;
    _value = value;
    _type = type;
    _color = (type == CardType::HEARTS || type == CardType::DIAMONDS) ? CardColor::RED : CardColor::BLACK;
    this->AddComponent(image);
}

Card::~Card()
{
    //dtor
}

void Card::Update(float deltaTime)
{

}
