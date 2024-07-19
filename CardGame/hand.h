#ifndef HAND_H
#define HAND_H

#include <vector>
#include "CardGame/card.h"

class Hand
{
public:
    Hand();
    virtual ~Hand();

    void AddCard(Card* card);
    void AddCards(std::vector<Card*> cards);

    void RemoveCard(int index);
    void RemoveCard(Card* card);

    void Clear();

    Card* GetCard(int index);
    int GetHandSize();

    // Game types are defined in the cardscene.h file as an enum class
    void SortHand(int gameType);
private:
    std::vector<Card*> _cards;
};

#endif
