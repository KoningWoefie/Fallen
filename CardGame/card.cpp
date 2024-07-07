#include "CardGame/card.h"

Card::Card(int value, CardType type)
{
    FallenUI::Image* image = new FallenUI::Image();
    image->width = 500;
    image->height = 700;
    _value = value;
    _type = type;
    _name = std::to_string(value) + "_of_";
    switch (_type)
    {
        case CardType::HEARTS:
            _name += "Hearts";
            break;
        case CardType::DIAMONDS:
            _name += "Diamonds";
            break;
        case CardType::CLUBS:
            _name += "Clubs";
            break;
        case CardType::SPADES:
            _name += "Spades";
            break;
        case CardType::JOKER:
            _name = "Joker";
            break;
    }
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
