//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_PLAYER_H
#define GINRUMMYBOT_PLAYER_H
#include "deck.h"

class Player {
public:
    Player();
    const std::vector<std::vector<int>>& getCards() const;
    void addCard(int, int);
    void makeMove(std::vector<std::vector<int>>&, const std::pair<int,int> &, Deck & discardPile);
    bool gin() const;
    int getScore() const;
    void setScore(int);
    void clearCards();
    bool canKnock() const;
    void filterMatched();
    int getValueOfUnmatched() const;
    int getNumCards();
private:
    int getValueOfCard(const std::pair<int,int>&) const;
    std::vector<std::vector<int>> cards;
//                                        = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    void discardCard(const std::pair<int,int>& card);
    std::vector<std::pair<int, int>> findRun(const std::pair<int, int>& cardToBeMatched) const;
    std::vector<std::pair<int, int>> findSet(const std::pair<int, int>& cardToBeMatched) const;
    int score = 0;
    std::vector<std::pair<int, int>> matched;
    std::vector<std::pair<int, int>> unmatched;
};

bool isConsecutive(const std::pair<int, int>&, const std::pair<int, int>&);
bool operator==(const Player&, const Player&);
#endif //GINRUMMYBOT_PLAYER_H
