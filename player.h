//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_PLAYER_H
#define GINRUMMYBOT_PLAYER_H
#include "card.h"
#include "deck.h"
#include "cardProperties.h"
#include <iterator>
class Player {
public:
    Player();
    const std::vector<Card>& getCards() const;
    void addCard(const Card&);
    void makeMove(const Card &, const Card &);
    bool gin() const;
    int getScore() const;
    void setScore(int);
    void clearCards();
    bool canKnock() const;
    void filterMatched();
    int getValueOfUnmatched() const;
private:
    void discardCard(const Card &);
    std::vector<Card> findRun(const Card&) const;
    std::vector<Card> findSet(const Card&) const;
    Deck deck;
    int score;
    std::vector<Card> matched;
    std::vector<Card> unmatched;
};

bool isConsecutiveFaceCard(const Card&, const Card&);
bool isConsecutive(const Card&, const Card&);
#endif //GINRUMMYBOT_PLAYER_H
