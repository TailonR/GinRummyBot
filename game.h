//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_GAME_H
#define GINRUMMYBOT_GAME_H
#include "player.h"
#include "deck.h"
class Game {
public:
    explicit Game(int);
    int getNumPlayers();
    void deal(Deck&);
    void play();
    std::vector<Player> getPlayers();
private:
    std::vector<Player> players;
    int numPlayers;
};

int checkNumPlayers(int);

#endif //GINRUMMYBOT_GAME_H
