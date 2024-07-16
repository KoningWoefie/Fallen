#ifndef CARD_H
#define CARD_H

#include <src/Core/object.h>
#include <src/UI/image.h>
#include <src/UI/button.h>
#include <src/UI/inputfield.h>

enum class CardType
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
    JOKER
};

enum class CardColor
{
    BLACK,
    RED,
    NONE
};

enum class CardImage
{
    ACE = 14,
    KING = 13,
    QUEEN = 12,
    JACK = 11,
    TEN = 10,
    NINE = 9,
    EIGHT = 8,
    SEVEN = 7,
    SIX = 6,
    FIVE = 5,
    FOUR = 4,
    THREE = 3,
    TWO = 2
};

class Card : public Object
{
public:
    Card(int value, CardType type);
    Card(CardImage ci, CardType type);
    virtual ~Card();

    virtual void Update(float deltaTime);

    std::string GetName() { return _name; };
private:
    int _value;
    CardType _type;
    CardColor _color;
    std::string _name;

    FallenUI::InputField* _input;
};

#endif
