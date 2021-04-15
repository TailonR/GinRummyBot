#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "game.h"
#include "mcts.h"
#include <iostream>
#include <Python.h>

int checking(int n) {
    return 4*n;
}

//Can use INFO macro to give context to why something failed, instead of couting
//Can define doctest to_string to stringify your types

TEST_CASE("Checking if doctest works") {
    CHECK(checking(4) == 16);
    CHECK(checking(5) == 20);
    CHECK(checking(16) == 64);
}

TEST_CASE("Checking Game Construction: number of players") {
    CHECK(Game().getNumPlayers() == 2);
}

TEST_CASE("Checking Deck Construction: size of decks") {
    CHECK(Deck(true).getNumCards() == 52); //stock
    CHECK(Deck().getNumCards() == 0); // discard
}

TEST_CASE("Deck operations: remove") {
    Deck deck(true);
    auto deck2 = deck;
    auto deck3 = deck;
    auto deck4 = deck;

    deck.removeTopCard();

    for(int i = 0; i < 5; i++)
        deck2.removeTopCard();

    for(int i = 0; i < 7; i++)
        deck3.removeTopCard();

    for(int i = 0; i < 17; i++)
        deck4.removeTopCard();

    CHECK(deck.getNumCards() == 51);
    CHECK(deck2.getNumCards() == 47);
    CHECK(deck3.getNumCards() == 45);
    CHECK(deck4.getNumCards() == 35);
}

TEST_CASE("Deck operations: topCard") {
    Deck deck(true);
    auto topCard = deck.topCard();

    CHECK(typeid(topCard) == typeid(std::pair<int, int>));
}

TEST_CASE("Checking Player operations: addCard") {
    std::pair<int, int> newCard = {3, 3};
    Player player;
    auto playerCardsBeforeAdd = player.getCards();
    int valueAtIndexBeforeAdd = playerCardsBeforeAdd[std::get<0>(newCard)][std::get<1>(newCard)];
    player.addCard(std::get<0>(newCard), std::get<1>(newCard));
    auto playerCardsAfterAdd = player.getCards();
    int valueAtIndexAfterAdd = playerCardsAfterAdd[std::get<0>(newCard)][std::get<1>(newCard)];

    CHECK(valueAtIndexBeforeAdd == 0);
    CHECK(valueAtIndexAfterAdd == 1);
}

TEST_CASE("Game operations: deal") {
    Game game;
    Deck deck(true);

    game.deal(deck);
    auto thePlayers = game.getPlayers();


    CHECK(thePlayers[0].getNumCards() == 10);
    CHECK(thePlayers[1].getNumCards() == 10);
    CHECK(deck.getNumCards() == 32);
}

TEST_CASE("Game operations: knocking") {
    Game game;
    Player player1 = game.getPlayers()[0];
    Player player2 = game.getPlayers()[1];

    // Generate Cards where a player can knock
    std::vector<std::pair<int, int>> knockableHand = {{0, 4}, {0, 5}, {0,6}, {0, 7}, {0, 8},
                                                      {0, 9}, {0, 10}, {1, 1}, {2, 2}, {3, 3}};

    // Generate Cards where a player can't knock
    std::vector<std::pair<int, int>> nonknockableHand = { {0, 4}, {0, 5}, {0, 6}, {0, 7}, {2, 8},
                                                          {0, 9}, {0, 10}, {1, 1}, {2, 2}, {3, 3}};
    for(const auto& card: knockableHand) {
        player1.addCard(std::get<0>(card), std::get<1>(card));
    }
    player1.filterMatched();

    for(const auto& card: nonknockableHand) {
        player2.addCard(std::get<0>(card), std::get<1>(card));
    }
    player2.filterMatched();

    CHECK(player1.canKnock() == true);
    CHECK(player2.canKnock() == false);
}

TEST_CASE("Game operations: going gin") {
    Game game;
    Player player1 = game.getPlayers()[0];
    Player player2 = game.getPlayers()[1];

    // Generate Cards where a player can go gin
    std::vector<std::pair<int, int>> ginHand = {{0, 4}, {0, 5}, {0,6}, {0, 7}, {0, 8},
                                                      {0, 9}, {0, 10}, {0, 1}, {0, 2}, {0, 3}};

    // Generate Cards where a player can't knock
    std::vector<std::pair<int, int>> nonGinHand = { {0, 4}, {0, 5}, {0, 6}, {0, 7}, {2, 8},
                                                          {0, 9}, {0, 10}, {1, 1}, {2, 2}, {3, 3}};


    for(const auto& card: ginHand) {
        player1.addCard(std::get<0>(card), std::get<1>(card));
    }
    player1.filterMatched();

    for(const auto& card: nonGinHand) {
        player2.addCard(std::get<0>(card), std::get<1>(card));
    }
    player2.filterMatched();

    CHECK(player1.gin() == true);
    CHECK(player2.gin() == false);
}

//TEST_CASE("Game AI: MCTS search") {
//    MCTS mcts;
//    Deck theDeck;
//    int searchTime = 5;
//    std::vector<Player> players;
//    int turn = 0;
//}


int main(int argc, char** argv) {
    ///////////////////////////////////////////// Run the tests /////////////////////////////////////////////
    doctest::Context ctx;
    ctx.setOption("abort-after", 1);  // default - stop after 5 failed asserts
    ctx.applyCommandLine(argc, argv); // apply command line - argc / argv
    ctx.setOption("no-breaks", true); // override - don't break in the debugger
    int res = ctx.run();              // run test cases unless with --no-run
    if(ctx.shouldExit())              // query flags (and --exit) rely on this
        return res;                   // propagate the result of the tests
    /////////////////////////////////////////// Done Run the tests //////////////////////////////////////////

    //////////////////////////////////////////// Playing the Game ///////////////////////////////////////////
    //Initilize the game
    Game game;

    //Which players are being played by user and by ai
    std::vector<bool> whosPlaying; // are the players going to be played by user
    bool userResponse;
    for(auto index = game.getPlayers().begin(); index != game.getPlayers().end(); index++) {
        std::cout << "Is player " << (index - game.getPlayers().begin())+1 << " going to be played by a user or ai";
        std::cout << " (0 = no | 1 = yes)" << std::endl;
        std::cin >> userResponse;
        whosPlaying.push_back(userResponse);
    }

    std::cout << "Note: Suits are represented as a number" << std::endl;
    std::cout << "      0 - Hearts\n"
                 "      1 - Diamonds\n"
                 "      2 - Spades\n"
                 "      3 - Clubs\n"
                 "Ranks are represented as numbers from 0 to 12\n"
                 "      0 - A\n"
                 "      10 - J\n"
                 "      11 - Q\n"
                 "      12 - K\n"
                 "      everything else: the rank is the number (e.g 2 - 2, 3 - 3)" << std::endl;
    std::cout << "Cards are displayed in the following order" << std::endl;
    std::cout << "[Rank, Suit, Value]" << std::endl;
    std::cout << std::endl;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.ignore();
    while (true) {
        if (std::cin.get() == '\n')
            break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    //Start the game
    game.gamePlay(whosPlaying);
    ///////////////////////////////////////// Done Playing the Game /////////////////////////////////////////


    return res; // + your_program_res
}
