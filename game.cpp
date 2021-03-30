//
// Created by renew on 3/18/2021.
//

#include "game.h"
Game::Game(int num): numPlayers(players.size()), players(checkNumPlayers(num)) {
    for(int playerIndex = 0; playerIndex < numPlayers; playerIndex++) {
        players[playerIndex] = Player();
    }
}

int checkNumPlayers(int number) {
    return (number == 2 || number == 3 || number == 4)? number: 0;
}

int Game::getNumPlayers() {
    return players.size();
}

std::vector<Player> Game::getPlayers() {
    return players;
}


void Game::deal(Deck& theDeck) {
    for(int numCardsInHand = 0; numCardsInHand < 10; numCardsInHand++) {
        for(auto & player: players) {
            auto newCard = theDeck.topCard();
            player.addCard(newCard);
            theDeck.removeTopCard();
        }
    }
}

void Game::play() {}
