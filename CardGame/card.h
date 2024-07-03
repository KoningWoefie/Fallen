#ifndef CARD_H
#define CARD_H

#include <src/Core/object.h>
#include <src/UI/image.h>

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

class Card : public Object
{
public:
    Card(int value, CardType type);
    virtual ~Card();

    virtual void Update(float deltaTime);
private:
    int _value;
    CardType _type;
    CardColor _color;
};

#endif
