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
    void markGameBoard(int playerTurn, const std::pair<int, int>& card, int possibleNewState1, int possibleNewState2);
    void clearBoard();
private:
    void printPlayerCards(std::ostream&, int turn);
    void initializeRandomNumberGenerator(int);
    int generateRandomNumber();
    void collectPlayerCards(int, std::vector<std::pair<int, int>>&);
    CardProperties standardCards;
    std::vector<std::vector<int>> gameBoard;
    std::mt19937 mt;
    std::uniform_int_distribution<int> randomNumberGenerator;
    std::vector<int> chooseTheOrder();
    std::vector<Player> players;
    std::vector<int> playerOrder;
};

#endif //GINRUMMYBOT_GAME_H
