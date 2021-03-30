//
// Created by renew on 3/18/2021.
//

#include "deck.h"
Deck::Deck(bool forPlayer): cards(createDeck(forPlayer)) {}

std::vector<Card>& Deck::getCards(){
    return cards;
}

std::vector<Card> createDeck(bool forPlayer) {
    if(forPlayer) {
        return std::vector<Card>(10, Card("",""));
    } else {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::vector<Card> fullDeck;
        const std::vector<std::string> cardRanks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        const std::vector<std::string> cardSuits {"club", "diamond", "heart", "spade"};
        for (const auto& rank: cardRanks)
            for (const auto& suit: cardSuits)
                fullDeck.emplace_back(Card(rank, suit));

        std::shuffle(fullDeck.begin(), fullDeck.end(), std::default_random_engine(seed));
        return fullDeck;
    }
}

Card Deck::topCard() {
    return cards[0];
}

void Deck::removeTopCard() {
    if (!cards.empty())
        cards.erase(cards.begin());
}

int Deck::getNumCards(){
    return cards.size();
}


