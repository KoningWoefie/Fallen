#include "CardGame/card.h"
#include "src/UI/button.h"
#include "src/UI/inputfield.h"

Card::Card(int value, CardType type)
{
    FallenUI::Image* image = new FallenUI::Image();
    image->width = 500;
    image->height = 700;


    FallenUI::Button* button = new FallenUI::Button();
    _input = new FallenUI::InputField();

    button->SetOnPress(std::bind(&FallenUI::InputField::ToggleRegisterInput, _input));

    _value = value;
    _type = type;
    switch(value)
    {
        case 14:
            _name = "ace_of_";
            break;
        case 13:
            _name = "king_of_";
            break;
        case 12:
            _name = "queen_of_";
            break;
        case 11:
            _name = "jack_of_";
            break;
        default:
            _name = std::to_string(value) + "_of_";
            break;
    }
    switch (_type)
    {
        case CardType::HEARTS:
            _name += "hearts";
            break;
        case CardType::DIAMONDS:
            _name += "diamonds";
            break;
        case CardType::CLUBS:
            _name += "clubs";
            break;
        case CardType::SPADES:
            _name += "spades";
            break;
        case CardType::JOKER:
            _name = "joker";
            break;
    }
    _color = (type == CardType::HEARTS || type == CardType::DIAMONDS) ? CardColor::RED : CardColor::BLACK;
    image->AddSprite(new Sprite("assets/cards/" + _name + ".tga"));
    this->AddComponent(image);
    this->AddComponent(button);
    this->AddComponent(_input);
}

Card::Card(CardImage ci, CardType type)
{
    FallenUI::Image* image = new FallenUI::Image();
    image->width = 500;
    image->height = 700;


    FallenUI::Button* button = new FallenUI::Button();
    _input = new FallenUI::InputField();

    button->SetOnPress(std::bind(&FallenUI::InputField::ToggleRegisterInput, _input));

    _value = (int)ci;
    _type = type;
    switch(ci)
    {
        case CardImage::ACE:
            _name = "ace_of_";
            break;
        case CardImage::KING:
            _name = "king_of_";
            break;
        case CardImage::QUEEN:
            _name = "queen_of_";
            break;
        case CardImage::JACK:
            _name = "jack_of_";
            break;
        default:
            _name = std::to_string((int)ci) + "_of_";
            break;
    }
    switch (_type)
    {
        case CardType::HEARTS:
            _name += "hearts";
            break;
        case CardType::DIAMONDS:
            _name += "diamonds";
            break;
        case CardType::CLUBS:
            _name += "clubs";
            break;
        case CardType::SPADES:
            _name += "spades";
            break;
        case CardType::JOKER:
            _name = "joker";
            break;
    }
    _color = (type == CardType::HEARTS || type == CardType::DIAMONDS) ? CardColor::RED : CardColor::BLACK;
    image->AddSprite(new Sprite("assets/cards/" + _name + ".png"));
    this->AddComponent(image);
    this->AddComponent(button);
    this->AddComponent(_input);
}

Card::~Card()
{
    //dtor
}

void Card::Update(float deltaTime)
{
}
