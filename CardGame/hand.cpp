#include "CardGame/hand.h"
#include <algorithm>

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::AddCard(Card* card)
{
    _cards.push_back(card);
}

void Hand::AddCards(std::vector<Card *> cards)
{
    for (int i = 0; i < cards.size(); i++)
    {
        _cards.push_back(cards[i]);
    }
}

void Hand::RemoveCard(Card* card)
{
    for (int i = 0; i < _cards.size(); i++)
    {
        if (_cards[i] == card)
        {
            _cards.erase(_cards.begin() + i);
            break;
        }
    }
}

void Hand::RemoveCard(int index)
{
    _cards.erase(_cards.begin() + index);
}

void Hand::Clear()
{
    _cards.clear();
}

Card* Hand::GetCard(int index)
{
    return _cards[index];
}

int Hand::GetHandSize()
{
    return _cards.size();
}

bool CompareCardByValue(Card* c1, Card* c2)
{
    if(c1->GetValue() < c2->GetValue())
    {
        return true;
    }
    return false;
};

void Hand::SortHand(int gameType)
{
    std::vector<Card*> sortedHand;
    std::vector<Card*> suitHand;
    std::vector<Card*> valuesOfHand;
    switch (gameType)
    {
        case 0:
            // Sort by suit
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < _cards.size(); j++)
                {
                    if ((int)_cards[j]->GetType() == i)
                    {
                        suitHand.push_back(_cards[j]);
                    }
                }
                std::sort(suitHand.begin(), suitHand.end());
                for (int k = 0; k < suitHand.size(); k++)
                {
                    sortedHand.push_back(suitHand[k]);
                }
                suitHand.clear();
            }
            _cards = sortedHand;
            sortedHand.clear();
            break;
        default:
            std::cout << "Invalid game type" << "\n";
            break;
    }
}
