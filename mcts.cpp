//
// Created by renew on 3/30/2021.
//

#include "mcts.h"
MCTS::MCTS(): mt(std::random_device{}()) {}

// Searches the search space for the best currentDiscardCard and returns the index to that currentDiscardCard
// Might want the discard pile for the NN
int MCTS::search(const Deck & theDeck, int searchTime, std::vector<Player> players, int turn) {
    return -1; // dummy
}

// This simulates finishing the game if the proposed Node was chosen
// Eventually gonna need player type
std::shared_ptr<Player> MCTS::simulation(int turn, std::vector<Player> players, int & nodeCount) {
    return std::make_shared<Player>(players[0]); // dummy;
}

void MCTS::setUniformDistribution(int max) {
    std::uniform_int_distribution<int> range(0, max);
    dist = range;
}
