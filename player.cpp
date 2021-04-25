//
// Created by renew on 3/18/2021.
//

#include "player.h"
Player::Player(): cards(std::vector<std::vector<int>>(4, std::vector<int>(14, 0))) {}

const std::vector<std::vector<int>>& Player::getCards() const {
    return cards;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score += newScore;
}

void Player::addCard(int suit, int rank) {
    cards[suit][rank] = 1;
    unmatched.emplace_back(suit, rank);
}

int Player::getValueOfCard(const std::pair<int, int> & card) const {
    CardProperties standardCards;
    int suit = std::get<0>(card);
    int rank = std::get<1>(card);
    return standardCards.cards[suit][rank];
}

void Player::filterMatched() {
    auto cardIter = unmatched.begin();
    while (cardIter != unmatched.end()) {
        auto run = findRun(*cardIter);
        if (run.size() >= 3) {
            for(const auto& cardInRun: run) {
                auto found = std::find(unmatched.begin(), unmatched.end(), cardInRun);
                cardIter = unmatched.erase(found);
            }
        }
        auto set = findSet(*cardIter);
        if (set.size() >= 3) {
            for(const auto& cardInSet: set) {
                auto found = std::find(unmatched.begin(), unmatched.end(), cardInSet);
                cardIter = unmatched.erase(found);
            }
        }

        if(run.size() < 3 && set.size() < 3)
            ++cardIter;
    }
}


void Player::makeMove(std::vector<std::vector<int>>& gameBoard, int playerTurn, const std::pair<int,int> & cardToDiscard, Deck & discardPile) {
    // Update Game Board
    gameBoard[std::get<0>(cardToDiscard)][std::get<1>(cardToDiscard)] = CardProperties::CardStates::DISCARD;


    // Discard the given discard card from your deck
    discardCard(cardToDiscard);

    // Add that card to the discard pile
    discardPile.addCard(std::get<0>(cardToDiscard), std::get<1>(cardToDiscard));

    // Now filter out the matched cards
    filterMatched();
}

bool isConsecutive(const std::pair<int, int>& firstCard, const std::pair<int, int>& secondCard) {
    int rankOfFirst = std::get<1>(firstCard);
    int rankOfSecond = std::get<1>(secondCard);
    if(rankOfFirst == 0) {
        return (rankOfSecond == 2);
    } else {
        return (std::abs(rankOfFirst - rankOfSecond) < 2);
    }
}

/// This could eventually be part of the evaluation function
std::vector<std::pair<int, int>> Player::findRun(const std::pair<int, int>& cardToBeMatched) const {
    std::vector<std::pair<int, int>> tempVec;
    auto tempCardToBeMatched = cardToBeMatched;
    for(const auto& card: unmatched) {
        if(std::get<0>(card) == std::get<0>(tempCardToBeMatched)) {
            if(isConsecutive(card, tempCardToBeMatched)) {
                tempVec.push_back(card);
                tempCardToBeMatched = card;
            }
        }
    }
    return tempVec;
}

// This could eventually be part of the evaluation function
std::vector<std::pair<int, int>> Player::findSet(const std::pair<int, int>& cardToBeMatched) const {
    std::vector<std::pair<int, int>> tempVec;
    auto tempCardToBeMatched = cardToBeMatched;
    for(const auto& card: unmatched) {
        if(std::get<1>(card) == std::get<1>(tempCardToBeMatched)) {
            tempVec.push_back(card);
            tempCardToBeMatched = card;
        }
    }
    return tempVec;
}

void Player::clearCards() {
    for(auto & card : cards)
        for (int rank = 0; rank < cards[0].size(); rank++)
            card[rank] = 0; // This is going to set all cards to 0 (even if they were already 0)

    unmatched.clear();
}

int Player::getNumCards() {
    int numCards = 0;
    for(const auto& suit: cards)
        for(const auto& rank: suit)
            if (rank == 1)
                numCards++;

    return numCards;
}

void Player::discardCard(const std::pair<int,int>& card) {
    int suit = std::get<0>(card);
    int rank = std::get<1>(card);
    cards[suit][rank] = 0;

    auto cardFoundInUnmatched = std::find_if(unmatched.begin(), unmatched.end(), [suit, rank](auto card) {
        return (std::get<0>(card) == suit && std::get<1>(card) == rank);
    });

    if(cardFoundInUnmatched != unmatched.end()) {
        unmatched.erase(cardFoundInUnmatched);
    }
}

int Player::getValueOfUnmatched() const {
    int totalValueOfUnmatched = 0;
    for(const auto& card: unmatched) {
        int valueOfCard = getValueOfCard(card);
        totalValueOfUnmatched += valueOfCard;
    }

    return totalValueOfUnmatched;
}

bool Player::canKnock() const {
    return (getValueOfUnmatched() < 10);
}

bool Player::gin() const {
    std::cout << std::endl;
    return (unmatched.empty());
}

bool operator==(const Player& lhs, const Player& rhs) {
    return (lhs.getCards() == rhs.getCards());
}
