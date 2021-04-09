#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include "game.h"

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

TEST_CASE("Checking Card Construction") {
    Card firstCard("3", "clubs");
    Card secondCard("4", "diamond");
    Card thirdCard("8", "spades");
    Card fourthCard("10", "spades");
    Card fifthCard("K", "spades");
    Card sixthCard("Q", "spades");
    Card seventhCard("J", "spades");

    CHECK(firstCard.getValue() == 3);
    CHECK(secondCard.getValue() == 4);
    CHECK(thirdCard.getValue() == 8);
    CHECK(fourthCard.getValue() == 10);
    CHECK(fifthCard.getValue() == 10);
    CHECK(sixthCard.getValue() == 10);
    CHECK(seventhCard.getValue() == 10);
}

TEST_CASE("Checking Deck Construction: size of decks") {
    CHECK(Deck(false).getNumCards() == 52);
    CHECK(Deck(true).getNumCards() == 0);
}

TEST_CASE("Checking Deck Construction: Default cards") {
    Deck deck(false);
    std::vector<std::string> ranks;
    std::vector<std::string> suits;
    int numCards = deck.getNumCards();
    for (const auto &card: deck.getCards()) {
        if (std::find(ranks.begin(), ranks.end(), card.getRank()) == ranks.end())
            ranks.push_back(card.getRank());

        if (std::find(suits.begin(), suits.end(), card.getSuit()) == suits.end())
            suits.push_back(card.getSuit());
    }

    CHECK(numCards == 52);
    CHECK(ranks.size() == 13);
    CHECK(suits.size() == 4);
}

TEST_CASE("Deck operations: remove") {
    Deck deck(false);
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

    CHECK(deck.getCards().size() == 51);
    CHECK(deck2.getCards().size() == 47);
    CHECK(deck3.getCards().size() == 45);
    CHECK(deck4.getCards().size() == 35);
}

TEST_CASE("Deck operations: topCard") {
    Deck deck(false);
    auto tempDeck = deck;
    auto topCard = deck.topCard();
    for(int i = 0; i < 5; i++)
        tempDeck.removeTopCard();
    auto newTopCard = tempDeck.topCard();

    const auto& deck2 = deck;
    auto tempDeck2 = deck;
    for(int i = 0; i < 50; i++)
        tempDeck2.removeTopCard();
    auto topCard2 = tempDeck2.topCard();

    CHECK(topCard == deck.getCards()[0]);
    CHECK(newTopCard == tempDeck.getCards()[0]);
    CHECK(newTopCard == deck.getCards()[5]);

    CHECK(topCard2 == tempDeck2.getCards()[0]);
    CHECK(topCard2 == deck2.getCards()[50]);
}


TEST_CASE("Checking Player operations: addCard") {
    Card newCard("3", "club");
    Player player;
    player.addCard(newCard);
    auto playerCards = player.getCards();
    auto placeInDeck = std::find_if(playerCards.begin(), playerCards.end(), [newCard](const Card& card) {
        if (card == newCard)
            return true;
        return false;
    });

    CHECK(placeInDeck != playerCards.end());
}

TEST_CASE("Game operations: deal") {
    Game game;
    Deck deck(false);

    game.deal(deck);
    bool deck2NotBlank = true;
    for(const auto& player: game.getPlayers())
        for(auto& card: player.getCards())
            if(card.getRank().empty() && card.getSuit().empty())
                deck2NotBlank = false;

    CHECK(deck2NotBlank == true);
    CHECK(deck.getNumCards() == 32);
}

TEST_CASE("Game operations: knocking") {
    Game game;
    Player player1 = game.getPlayers()[0];
    Player player2 = game.getPlayers()[1];

    // Generate Cards where a player can knock
    std::vector<Card> knockableHand = { Card("4", "heart"), Card("5", "heart"), Card("6", "heart"), Card("7", "heart"),
                                        Card("8", "heart"), Card("9", "heart"), Card("10", "heart"), Card("A", "diamond"),
                                        Card("2", "spade"), Card("3", "club")};

    // Generate Cards where a player can't knock
    std::vector<Card> nonknockableHand = { Card("4", "heart"), Card("5", "heart"), Card("6", "heart"), Card("7", "heart"),
                                        Card("8", "spade"), Card("9", "heart"), Card("10", "heart"), Card("A", "diamond"),
                                        Card("2", "spade"), Card("3", "club")};

    for(const auto& card: knockableHand) {
        player1.addCard(card);
    }
    player1.filterMatched();

    for(const auto& card: nonknockableHand) {
        player2.addCard(card);
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
    std::vector<Card> ginHand = {Card("4", "heart"), Card("5", "heart"), Card("6", "heart"), Card("7", "heart"),
                                 Card("8", "heart"), Card("9", "heart"), Card("10", "heart"), Card("A", "heart"),
                                 Card("2", "heart"), Card("3", "heart")};

    // Generate Cards where a player can't knock
    std::vector<Card> nonGinHand = {Card("4", "heart"), Card("5", "heart"), Card("6", "heart"), Card("7", "heart"),
                                    Card("8", "spade"), Card("9", "heart"), Card("10", "heart"), Card("A", "diamond"),
                                    Card("2", "spade"), Card("3", "club")};

    for(const auto& card: ginHand) {
        player1.addCard(card);
    }
    player1.filterMatched();

    for(const auto& card: nonGinHand) {
        player2.addCard(card);
    }
    player2.filterMatched();

    CHECK(player1.gin() == true);
    CHECK(player2.gin() == false);
}

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

    //Start the game
    game.gamePlay(whosPlaying);
    ///////////////////////////////////////// Done Playing the Game /////////////////////////////////////////


    return res; // + your_program_res
}
