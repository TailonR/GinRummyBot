//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_PLAYER_H
#define GINRUMMYBOT_PLAYER_H
#include "card.h"
#include "deck.h"
class Player {
public:
    Player();
    Deck getDeck() const;
    int getNumOfCards();
    void addCard(const Card&);
private:
    Deck deck;
};
#endif //GINRUMMYBOT_PLAYER_H
