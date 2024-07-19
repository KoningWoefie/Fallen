#include "CardGame/deck.h"

Deck::Deck(bool useJokers, int jokerCount)
{
    _totalLength = 52;
    if(useJokers) _totalLength += jokerCount;

    for(int i = 2; i < 15; i++)
    {
        _cards.push_back(new Card(i, CardType::HEARTS));
    }
    for(int i = 2; i < 15; i++)
    {
        _cards.push_back(new Card(i, CardType::DIAMONDS));
    }
    for(int i = 2; i < 15; i++)
    {
        _cards.push_back(new Card(i, CardType::CLUBS));
    }
    for(int i = 2; i < 15; i++)
    {
        _cards.push_back(new Card(i, CardType::SPADES));
    }
    if(useJokers)
    {
        for(int i = 0; i < jokerCount; i++)
        {
            _cards.push_back(new Card(15, CardType::JOKER));
        }
    }

    Shuffle();
}

Deck::~Deck()
{
    for(Card* c : _cards)
    {
        delete c;
        c = nullptr;
    }
}

void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(_cards.begin(), _cards.end(), gen);
}

Card* Deck::Draw()
{
    Card* c = _cards.back();
    _cards.pop_back();
    return c;
}
