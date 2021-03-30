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
class Deck{
public:
    explicit Deck(bool forPlayer = false);
    std::vector<Card>& getCards();
    int getNumCards();
    Card topCard();
    void removeTopCard();
private:
    std::vector<Card> cards;
};

std::vector<Card> createDeck(bool forPlayer);
int typeOfDeck(bool); // type of deck means to whom does it belong
//  if it is a player's deck then it's going to
//  be restricted to 10 cards, else its 52 or
//  the number of cards left over from the players'
//  hands
#endif //GINRUMMYBOT_DECK_H
