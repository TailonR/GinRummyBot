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
            CHECK(Game(1).getNumPlayers() == 0);
            CHECK(Game(2).getNumPlayers() == 2);
            CHECK(Game(3).getNumPlayers() == 3);
            CHECK(Game(4).getNumPlayers() == 4);
            CHECK(Game(5).getNumPlayers() == 0);
            CHECK(Game(6).getNumPlayers() == 0);
            CHECK(Game(7).getNumPlayers() == 0);
}

TEST_CASE("Checking Player Construction") {
            CHECK(Player().getNumOfCards() == 10);
}

TEST_CASE("Checking Game Construction: Players") {
    Game game2(2);
    Game game3(3);
    Game game4(4);

            CHECK(game2.getPlayers()[0].getNumOfCards() == 10);
            CHECK(game2.getPlayers()[1].getNumOfCards() == 10);

            CHECK(game3.getPlayers()[0].getNumOfCards() == 10);
            CHECK(game3.getPlayers()[1].getNumOfCards() == 10);
            CHECK(game3.getPlayers()[2].getNumOfCards() == 10);

            CHECK(game4.getPlayers()[0].getNumOfCards() == 10);
            CHECK(game4.getPlayers()[1].getNumOfCards() == 10);
            CHECK(game4.getPlayers()[2].getNumOfCards() == 10);
            CHECK(game4.getPlayers()[3].getNumOfCards() == 10);

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
            CHECK(Deck(true).getNumCards() == 10);
}

TEST_CASE("Checking Deck Construction: Player cards") {
    Deck playerDeck(true);
    int allBlank = true;
    auto cardsInDeck = playerDeck.getCards();
    for(const auto& card: playerDeck.getCards()) {
        if(!card.getRank().empty())
            allBlank = false;

        if(!card.getSuit().empty())
            allBlank = false;
    }

            CHECK(allBlank == true);
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

    auto deck2 = deck;
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
    auto playerDeck = player.getDeck();
    auto placeInDeck = std::find_if(playerDeck.getCards().begin(), playerDeck.getCards().end(), [newCard](const Card& card) {
        if (card == newCard)
            return true;
        return false;
    });

            CHECK(placeInDeck != playerDeck.getCards().end());
}

TEST_CASE("Game operations: deal") {
    Game game2(2);
    Game game3(3);
    Game game4(4);
    Deck deck(false);
    auto deckFor3 = deck;
    auto deckFor4 = deck;

    game2.deal(deck);
    bool notBlank = true;
    for(const auto& player: game2.getPlayers())
        for(auto& card: player.getDeck().getCards())
            if(card.getRank().empty() && card.getSuit().empty())
                notBlank = false;

    game3.deal(deckFor3);
    for(const auto& player: game3.getPlayers())
        for(const auto& card: player.getDeck().getCards())
            if(card.getRank().empty() && card.getSuit().empty())
                notBlank = false;

    game4.deal(deckFor4);
    for(const auto& player: game4.getPlayers())
        for(const auto& card: player.getDeck().getCards())
            if(card.getRank().empty() && card.getSuit().empty())
                notBlank = false;

            CHECK(notBlank == true);
            CHECK(deck.getNumCards() == 32);
            CHECK(deckFor3.getNumCards() == 22);
            CHECK(deckFor4.getNumCards() == 12);
}


int main(int argc, char** argv) {
    ///////////////////////////////////////////// Run the tests /////////////////////////////////////////////
    doctest::Context ctx;
    ctx.setOption("abort-after", 5);  // default - stop after 5 failed asserts
    ctx.applyCommandLine(argc, argv); // apply command line - argc / argv
    ctx.setOption("no-breaks", true); // override - don't break in the debugger
    int res = ctx.run();              // run test cases unless with --no-run
    if(ctx.shouldExit())              // query flags (and --exit) rely on this
        return res;                   // propagate the result of the tests
    /////////////////////////////////////////// Done Run the tests //////////////////////////////////////////

    return res; // + your_program_res
}
