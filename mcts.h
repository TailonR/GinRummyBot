//
// Created by renew on 3/30/2021.
//

#ifndef GINRUMMYBOT_MCTS_H
#define GINRUMMYBOT_MCTS_H
#include <vector>
#include <memory>
#include "player.h"
#include "deck.h"
class MCTS {
    // The mcts will find whether it's best to choose from the discard and the best currentDiscardCard to insert and best currentDiscardCard to discard.
    //  This effectively means that it returns a pair<bool, pair<Card, Card>>
    //      The bool is whether to choose from the discard
    //          The pair is the best currentDiscardCard to insert and the best currentDiscardCard to discard

    // The neural network will take the player's deck, the discard pile, and a currentDiscardCard to look up and perhaps return the
    //  likelihood that the other player has a currentDiscardCard
public:
    MCTS();
    int search(const Deck & theDeck, int searchTime, std::vector<Player> players, int turn);
    std::shared_ptr<Player> simulation(int turn, std::vector<Player> players, int & nodeCount);
    void setUniformDistribution(int max);
private:
    int nodesProcessed = 0;
    std::uniform_int_distribution<int> dist;
    std::mt19937 mt;
};


#endif //GINRUMMYBOT_MCTS_H
