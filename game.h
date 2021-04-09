//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_GAME_H
#define GINRUMMYBOT_GAME_H
#include "player.h"
#include "deck.h"
#include <random>
#include <iostream>
#include <numeric>
class Game {
public:
    Game();
    int getNumPlayers();
    void deal(Deck&);
    void gamePlay(const std::vector<bool>&);
    std::pair<int, int> playRound(const std::vector<bool>&);
    const std::vector<Player>& getPlayers();
    int roundIsWon();
    bool gameIsWon();
private:
    void initializeRandomNumberGenerator(int);
    int generateRandomNumber();
    std::mt19937 mt;
    std::uniform_int_distribution<int> randomNumberGenerator;
    std::vector<int> chooseTheOrder();
    std::vector<Player> players;
    std::vector<int> playerOrder;

};

#endif //GINRUMMYBOT_GAME_H
