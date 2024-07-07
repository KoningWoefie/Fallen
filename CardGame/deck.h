#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "CardGame/card.h"

class Deck
{
public:
    Deck(bool useJokers = true, int jokerCount = 2);
    ~Deck();

    void Shuffle();
    Card Draw();

    void Regenerate();
private:
    std::vector<Card*> _cards;
    int _totalLength;
};

#endif
