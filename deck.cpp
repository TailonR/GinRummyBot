//
// Created by renew on 3/18/2021.
//

#include "deck.h"
Deck::Deck(bool forPlayer): cards(createDeck(forPlayer)) {}

const std::vector<Card>& Deck::getCards() const{
    return cards;
}

std::vector<Card>& Deck::getCards(){
    return cards;
}

void Deck::addCard(const Card& newCard) {
    if(cards.size() < 52) {
        cards.push_back(newCard);
    }
}

std::vector<Card> createDeck(bool forPlayer) {
    if(forPlayer) {
        return std::vector<Card>();
    } else {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::vector<Card> fullDeck;
        for (const auto& rank: CardProperties::getCardRanks())
            for (const auto& suit: CardProperties::getCardSuits())
                fullDeck.emplace_back(Card(rank, suit));

        std::shuffle(fullDeck.begin(), fullDeck.end(), std::default_random_engine(seed));
        return fullDeck;
    }
}

Card Deck::topCard() const {
    return cards[0];
}

void Deck::removeTopCard() {
    if (!cards.empty())
        cards.erase(cards.begin());
}

void Deck::removeCard(const Card& card){
    auto cardFound = std::find(cards.begin(), cards.end(), card);
    cards.erase(cardFound);
}

int Deck::getNumCards() const{
    return cards.size();
}

bool Deck::isEmpty() {
    return cards.empty();
}
