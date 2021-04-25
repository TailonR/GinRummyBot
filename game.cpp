//
// Created by renew on 3/18/2021.
//

#include "game.h"
Game::Game(): players({2, Player()}), mt(std::random_device{}()),
              gameBoard(std::vector<std::vector<int>>(4, std::vector<int>(14, CardProperties::CardStates::STOCK)))
                        {}


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

void Game::markGameBoard(int playerTurn, const std::pair<int, int>& card, int possibleNewState1, int possibleNewState2) {
    if (playerTurn) {
        gameBoard[std::get<0>(card)][std::get<1>(card)] = possibleNewState1;
    } else {
        gameBoard[std::get<0>(card)][std::get<1>(card)] = possibleNewState2;
    }
}

void Game::deal(Deck& theDeck) {
    playerOrder = chooseTheOrder();
    for(int numCardsInHand = 0; numCardsInHand < 10; numCardsInHand++) {
        for(const auto& playerIndex: playerOrder) {
            auto newCard = theDeck.topCard();
            players[playerIndex].addCard(std::get<0>(newCard), std::get<1>(newCard));
            theDeck.removeTopCard();
            markGameBoard(playerIndex, newCard, CardProperties::CardStates::P1CARD, CardProperties::CardStates::P0CARD);
        }
    }
    auto topCard = theDeck.topCard();
    markGameBoard(0, topCard, CardProperties::CardStates::TOPSTOCK, CardProperties::CardStates::TOPSTOCK);
}

int Game::roundIsWon() {
    for(auto playerIter = players.begin(); playerIter != players.end(); playerIter++) {
        if((*playerIter).gin())
            return (playerIter - players.begin());
    }
    return -1;
}

bool Game::gameIsWon() {
    return (players[0].getScore() > 100 || players[1].getScore() > 100);
}

void Game::printPlayerCards(std::ostream& os, int turn) {
    for (int suitIndex = 0; suitIndex < players[turn].getCards().size(); suitIndex++) {
        for(int rankIndex = 0; rankIndex < players[turn].getCards()[0].size(); rankIndex++) {
            if(players[turn].getCards()[suitIndex][rankIndex] == 1) {
                os << "[" << suitIndex << ", " << rankIndex << ", " << standardCards.cards[suitIndex][rankIndex] << "] ";
            }
        }
    }
    os << std::endl;
    os << std::endl;
}

void Game::collectPlayerCards(int turn, std::vector<std::pair<int, int>>& tempPlayerCards) {
    for(int suitIndex = 0; suitIndex != players[turn].getCards().size(); suitIndex++) {
        for(int rankIndex = 0; rankIndex != players[turn].getCards()[0].size(); rankIndex++) {
            if(players[turn].getCards()[suitIndex][rankIndex] == 1) {
                tempPlayerCards.emplace_back(suitIndex, rankIndex);
            }
        }
    }
}

void Game::clearBoard() {
    for (auto& suit: gameBoard) {
        for(auto& state: suit) {
            state = 0;
        }
    }
}

std::pair<int, int> Game::playRound(const std::vector<bool> & whosPlaying) {
    players[0].clearCards();
    players[1].clearCards();
    clearBoard();
    // Create the deck and deal out the cards
    Deck stock(true);
    deal(stock);

    bool roundOver = false;
    int knocked = 0;
    int turn = playerOrder[0];
    Deck discard; // the discard pile
    std::pair<int, int> topCard;
    topCard = stock.topCard();
    stock.removeTopCard();
    discard.addCard(std::get<0>(topCard), std::get<1>(topCard));
    markGameBoard(turn, topCard, CardProperties::CardStates::TOPDISCARD, CardProperties::CardStates::TOPDISCARD);
    topCard = stock.topCard();
    markGameBoard(0, topCard, CardProperties::CardStates::TOPSTOCK, CardProperties::CardStates::TOPSTOCK);
    while(!roundOver) {
        // Choose whether to take top stock card or top discard card
        initializeRandomNumberGenerator(1);
        int selectDiscard = generateRandomNumber();
        if (selectDiscard) {
            topCard = discard.topCard();
            discard.removeTopCard();
            players[turn].addCard(std::get<0>(topCard), std::get<1>(topCard));
            markGameBoard(turn, topCard, CardProperties::CardStates::P1CARD, CardProperties::CardStates::P0CARD);

        } else {
            topCard = stock.topCard();
            stock.removeTopCard();
            players[turn].addCard(std::get<0>(topCard), std::get<1>(topCard));
            markGameBoard(turn, topCard, CardProperties::CardStates::P1CARD, CardProperties::CardStates::P0CARD);
            topCard = stock.topCard();
            markGameBoard(0, topCard, CardProperties::CardStates::TOPSTOCK, CardProperties::CardStates::TOPSTOCK);
        }

        // Display the opponents cards only if the no user is playing
        if(whosPlaying[turn] == 0 && whosPlaying[(turn? 0: 1)] != 1){
            std::cout << "Here are player " << turn << "'s cards (with the new card listed last):" << std::endl;
            printPlayerCards(std::cout, turn);
        }

        int discardIndex;
        // If it's the user's turn
        if (whosPlaying[turn])  {
            std::vector<std::pair<int, int>> tempPlayerCards;
            // Display the player's cards
            std::cout << "Here your cards (with the new card listed last):" << std::endl;
            printPlayerCards(std::cout, turn);
            std::cout << std::endl;

            // Flatten the user's cards 2D vector into a 1D vector
            collectPlayerCards(turn, tempPlayerCards);

            std::cout << "What card you want to discard? (enter 0-9)" << std::endl;
            std::cin >> discardIndex;
            auto discardCard = tempPlayerCards[discardIndex];
            players[turn].makeMove(gameBoard, discardCard, discard);

            if (players[turn].canKnock()) {
                std::cout << "Do you want to knock? (0 = No, 1 = Yes)" << std::endl;
                std::cin >> knocked;
            }
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        } else { // If it's the bot's turn
            std::vector<std::pair<int, int>> tempPlayerCards;

            // Flatten the bot's cards 2D vector into a 1D vector
            collectPlayerCards(turn, tempPlayerCards);

            // Randomly choose what card to discard
            initializeRandomNumberGenerator(9);
            discardIndex = generateRandomNumber();
            auto discardCard = tempPlayerCards[discardIndex];
            players[turn].makeMove(gameBoard, discardCard, discard);

            // If player can knock, randomly choose to knock
            if (players[turn].canKnock()) {
                initializeRandomNumberGenerator(1);
                knocked = generateRandomNumber();
            }
        }

        turn = turn? 0: 1; // next players turn

        if (roundIsWon() == 1 || knocked) {
            roundOver = true;
        } else if (stock.isEmpty()) {
            roundOver = true;
            turn = -1;
        }
    }
    return {turn, knocked};  // First element: the index of who won (-1 if no one won)
                            // Second element: whether the player who won (or no player) knocked
}

void Game::gamePlay(const std::vector<bool>& whosPlaying) {
    bool gameOver = false;
    int roundCount = 0;
    while(!gameOver) {
        roundCount++;
        std::cout << "Start of Round #" << roundCount << std::endl;
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
                    // Add logic to get rid of currentDiscardCard if the opponent can (the undercut)
                    players[opponentIndex].setScore(opponentTotalUnmatchedValue - winnerTotalUnmatchedValue + 10);
                }
            }
        } else {
            int player0sUnmatchedValue = players[0].getValueOfUnmatched();
            int player1sUnmatchedValue = players[1].getValueOfUnmatched();
            players[0].setScore(player0sUnmatchedValue);
            players[1].setScore(player1sUnmatchedValue);
        }

        // Who is the user playing
        auto user = std::find_if(whosPlaying.begin(), whosPlaying.end(), [](const auto& userPlayer) { return (userPlayer); });
        if(user != whosPlaying.end()) {
            auto userIndex = user - whosPlaying.begin();
            std::cout << "Your score is: " << players[userIndex].getScore() << std::endl;
            std::cout << "Your opponent's score is: " << players[(userIndex? 0: 1)].getScore() << std::endl;
        } else {
            std::cout << "Player 0's score is: " << players[0].getScore() << std::endl;
            std::cout << "Player 1's score is: " << players[1].getScore() << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

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
