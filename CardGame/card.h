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

class Card : public Object
{
public:
    Card();
    virtual ~Card();

    virtual void Update(float deltaTime);
private:
    int value;
    CardType type;
};

#endif
