//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_DECK_H
#define GINRUMMYBOT_DECK_H
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <utility>
#include "cardProperties.h"
class Deck{
public:
    explicit Deck(bool = false);
    int getNumCards() const;
    std::pair<int,int> topCard() const;
    void removeTopCard();
    void addCard(int, int);
    void addCard(std::vector<std::vector<int>>&, int, int);
    bool isEmpty();

private:
    std::vector<std::pair<int, int>> cards;
};

std::vector<std::pair<int, int>> createCardList(bool stock);
#endif //GINRUMMYBOT_DECK_H
