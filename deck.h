//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_DECK_H
#define GINRUMMYBOT_DECK_H
#include "card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "cardProperties.h"
class Deck{
public:
    Deck() = default;
    explicit Deck(bool forPlayer);
    const std::vector<Card>& getCards() const;
    std::vector<Card>& getCards();
    int getNumCards() const;
    Card topCard() const;
    void removeTopCard();
    void removeCard(const Card&);
    void addCard(const Card&);
    bool isEmpty();
private:
    std::vector<Card> cards;
};

std::vector<Card> createDeck(bool forPlayer);
#endif //GINRUMMYBOT_DECK_H
