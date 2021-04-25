//
// Created by renew on 3/18/2021.
//

#include "deck.h"
Deck::Deck(bool stock): cards(createCardList(stock)) {}

void Deck::addCard(int suit, int rank) {
    if(cards.size() < 52)
        cards.insert(cards.begin(), std::make_pair(suit, rank));
}

void Deck::addCard(std::vector<std::vector<int>>& gameBoard, int suit, int rank) {
    if(cards.size() < 52)
        cards.insert(cards.begin(), std::make_pair(suit, rank));


    for(int suitIndex = 0; suitIndex < gameBoard.size(); suitIndex++) {
        for(int rankIndex = 0; rankIndex < gameBoard[0].size(); rankIndex++) {
            if (gameBoard[suitIndex][rankIndex] == CardProperties::CardStates::TOPDISCARD) {
                if (!(suitIndex == suit && rankIndex == rank)) {
                    gameBoard[suitIndex][rankIndex] = CardProperties::CardStates::DISCARD;
                }
            }
        }
    }
}

std::vector<std::pair<int, int>> createCardList(bool stock) {
    std::vector<std::pair<int, int>> returnVect;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (stock) {
        for (int suit = 0; suit < 4; suit++)
            for (int rank = 1; rank <= 13; rank++)
                returnVect.emplace_back(suit, rank);

        std::shuffle(returnVect.begin(), returnVect.end(), std::default_random_engine(seed));
        return returnVect;
    } else {
        return std::vector<std::pair<int, int>>();

    }
}

std::pair<int,int> Deck::topCard() const {
    return *cards.begin();
}

void Deck::removeTopCard() {
    if (!cards.empty())
        cards.erase(cards.begin());
}

int Deck::getNumCards() const{
    return cards.size();
}

bool Deck::isEmpty() {
    return cards.empty();
}
