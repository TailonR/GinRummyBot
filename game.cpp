//
// Created by renew on 3/18/2021.
//

#include "game.h"
Game::Game(): players({2, Player()}), mt(std::random_device{}()) {}

int Game::getNumPlayers() {
    return players.size();
}

const std::vector<Player> & Game::getPlayers() {
    return players;
}

std::vector<int> Game::chooseTheOrder() {
    // randomly chose the dealer
    initializeRandomNumberGenerator(1);
    int dealerIndex = generateRandomNumber();
    return {(dealerIndex? 0: 1), (dealerIndex? 1: 0)};
}

void Game::deal(Deck& theDeck) {
    playerOrder = chooseTheOrder();
    for(int numCardsInHand = 0; numCardsInHand < 10; numCardsInHand++) {
        for(const auto& playerIndex: playerOrder) {
            auto newCard = theDeck.topCard();
            players[playerIndex].addCard(newCard);
            theDeck.removeTopCard();
        }
    }
}

int Game::roundIsWon() {
    for(auto playerIter = players.begin(); playerIter != players.end(); playerIter++) {
        if((*playerIter).gin())
            return (playerIter - players.begin());
    }
    return -1;
}

bool Game::gameIsWon() {
    for(const auto& player: players) {
        return (player.getScore() > 100);
    }
    return false;
}

std::pair<int, int> Game::playRound(const std::vector<bool> & whosPlaying) {
    players[0].clearCards();
    players[1].clearCards();
    // Create the deck and deal out the cards
    Deck theDeck(false);
    deal(theDeck);

    bool roundOver = false;
    int knocked = 0;
    int turn = playerOrder[0];
    Deck discard; // the discard pile
    while(!roundOver) {
        //////////// Going to be part of MCTS ////////////
        // Turn over top card
        auto topCard = theDeck.topCard();
        discard.addCard(topCard);
        theDeck.removeTopCard();

        std::cout << "Current top Card" << std::endl;
        std::cout << "[" << topCard.getRank() << ", " << topCard.getSuit() << ", " << topCard.getValue() << "] ";
        std::cout << std::endl;
        std::cout << std::endl;

        // Display the opponents cards only if the user is not playing
        if(whosPlaying[turn] == 0 && whosPlaying[(turn? 0: 1)] != 1){
            std::cout << "Here are player " << turn << "'s cards:" << std::endl;
            for (const auto &card: players[turn].getCards()) {
                std::cout << "[" << card.getRank() << ", " << card.getSuit() << ", " << card.getValue() << "] ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }

        int takeTopCard;
        int discardIndex;
        if (whosPlaying[turn])  {
            // Display the player's cards
            std::cout << "Here your cards:" << std::endl;
            for(const auto& card: players[turn].getCards()) {
                std::cout << "[" << card.getRank() << ", " << card.getSuit() << ", " << card.getValue() << "] ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Do you want to take the top card? (0 = No, 1 = Yes)" << std::endl;
            std::cin >> takeTopCard;

            if(takeTopCard) {
                std::cout << "Which card do you want to discard? (enter 0-9)" << std::endl;
                std::cin >> discardIndex;
                auto discardCard = players[turn].getCards()[discardIndex];
                players[turn].makeMove(topCard, discardCard);
            }

            if (players[turn].canKnock()) {
                std::cout << "Do you want to knock? (0 = No, 1 = Yes)" << std::endl;
                std::cin >> knocked;
            }
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        } else {
            // Randomly choose to take the top card
            initializeRandomNumberGenerator(1);
            takeTopCard = generateRandomNumber();
            if(takeTopCard) {
                // Randomly choose what card to discard
                initializeRandomNumberGenerator(9);
                discardIndex = generateRandomNumber();
                auto discardCard = players[turn].getCards()[discardIndex];
                players[turn].makeMove(topCard, discardCard);
            }
            // If player can knock, randomly choose to knock
            if (players[turn].canKnock()) {
                initializeRandomNumberGenerator(1);
                knocked = generateRandomNumber();
            }
        }

        turn = turn? 0: 1; // next players turn

        if (roundIsWon() == 1 || knocked) {
            roundOver = true;
        } else if (theDeck.isEmpty()) {
            roundOver = true;
            turn = -1;
        }
    }
    return {turn, knocked};  // First element: the index of who won (-1 if no one won)
                            // Second element: whether the player who won (or no player) knocked
}

void Game::gamePlay(const std::vector<bool>& whosPlaying) {
    bool gameOver = false;
    while(!gameOver) {
        auto outcome = playRound(whosPlaying);
        if(std::get<0>(outcome) != -1) {
            int opponentIndex = std::get<0>(outcome)? 0: 1;
            int winnerIndex = std::get<0>(outcome);
            int opponentTotalUnmatchedValue = players[opponentIndex].getValueOfUnmatched();

            if (std::get<1>(outcome) == 0) {
                players[winnerIndex].setScore(opponentTotalUnmatchedValue + 20);
            } else {

                int winnerTotalUnmatchedValue = players[winnerIndex].getValueOfUnmatched();
                if (opponentTotalUnmatchedValue < winnerTotalUnmatchedValue) {
                    players[winnerIndex].setScore(winnerTotalUnmatchedValue - opponentTotalUnmatchedValue);
                } else {
                    // Add logic to get rid of card if the opponent can (the undercut)
                    players[opponentIndex].setScore(opponentTotalUnmatchedValue - winnerTotalUnmatchedValue + 10);
                }
            }
        }

        // Who is the user playing
        auto user = std::find_if(whosPlaying.begin(), whosPlaying.end(), [](const auto& userPlayer) { return (userPlayer); });
        auto userIndex = user - whosPlaying.begin();
        std::cout << "Your score is: " << players[userIndex].getScore() << std::endl;
        std::cout << "Your opponent's score is: " << players[(userIndex? 0: 1)].getScore() << std::endl;

        if (gameIsWon()) {
            gameOver = true;
        }
    }
}

void Game::initializeRandomNumberGenerator(int max) {
    std::uniform_int_distribution<int> generator(0, max);
    randomNumberGenerator = generator;
}

int Game::generateRandomNumber() {
    return randomNumberGenerator(mt);
}
