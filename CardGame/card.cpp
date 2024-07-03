#include "CardGame/card.h"

Card::Card()
{
    FallenUI::Image* image = new FallenUI::Image();
    image->width = 500;
    image->height = 700;
    this->AddComponent(image);
}

Card::~Card()
{
    //dtor
}

void Card::Update(float deltaTime)
{

}
