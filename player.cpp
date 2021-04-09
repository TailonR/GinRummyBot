//
// Created by renew on 3/18/2021.
//

#include "player.h"
#include <iostream>
Player::Player(): deck(Deck(true)), score(0) {}

const std::vector<Card>& Player::getCards() const {
    return deck.getCards();
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score += newScore;
}

void Player::addCard(const Card& newCard) {
    deck.addCard(newCard);
    unmatched.push_back(newCard);
}

void Player::filterMatched() {
    auto cardIter = unmatched.begin();
    while (cardIter != unmatched.end()) {
        auto run = findRun(*cardIter);
        if (run.size() >= 3) {
            for(const auto& cardInRun: run) {
                auto found = std::find(unmatched.begin(), unmatched.end(), cardInRun);
                cardIter = unmatched.erase(found);
                matched.push_back(cardInRun);
            }
        }
        auto set = findSet(*cardIter);
        if (set.size() >= 3) {
            for(const auto& cardInSet: set) {
                auto found = std::find(unmatched.begin(), unmatched.end(), cardInSet);
                cardIter = unmatched.erase(found);
                matched.push_back(cardInSet);
            }
        }

        if(run.size() < 3 && set.size() < 3)
            ++cardIter;
    }
}

void Player::makeMove(const Card& cardToInsert, const Card& cardToDiscard) {
    // Discard that card from your deck
    discardCard(cardToDiscard);

    // Now add the card to your deck
    addCard(cardToInsert);

    // Now filter the deck into matched and unmatched cards
    filterMatched();
}

bool isConsecutiveFaceCard(const Card& firstCard, const Card& secondCard) {
    if (firstCard.getRank() == "A") {
        return (secondCard.getRank() == "2");
    } else if (firstCard.getRank() == "J") {
        return (secondCard.getRank() == "10" || secondCard.getRank() == "Q");
    } else if (firstCard.getRank() == "Q") {
        return (secondCard.getRank() == "J" || secondCard.getRank() == "K");
    } else {
        return (secondCard.getRank() == "Q");
    }
}

bool isConsecutive(const Card& firstCard, const Card& secondCard) {
    if(!isAFaceCard(firstCard.getRank()) && !isAFaceCard(secondCard.getRank())) {
        // count consecutive as the same card and the next card
        return (std::abs(std::stoi(firstCard.getRank()) - std::stoi(secondCard.getRank())) < 2);
    } else if(isAFaceCard(firstCard.getRank())) {
        return isConsecutiveFaceCard(firstCard, secondCard);
    } else {
        return isConsecutiveFaceCard(secondCard, firstCard);
    }
}

// This could eventually be part of the evaluation function
std::vector<Card> Player::findRun(const Card& cardToBeMatched) const {
    std::vector<Card> tempVec;
    auto tempCardToBeMatched = cardToBeMatched;
    for(const auto& card: unmatched) {
        if(card.getSuit() == tempCardToBeMatched.getSuit()) {
            if(isConsecutive(card, tempCardToBeMatched)) {
                tempVec.push_back(card);
                tempCardToBeMatched = card;
            }
        }
    }
    return tempVec;
}

// This could eventually be part of the evaluation function
std::vector<Card> Player::findSet(const Card& cardToBeMatched) const {
    std::vector<Card> tempVec;
    auto tempCardToBeMatched = cardToBeMatched;
    for(const auto& card: unmatched) {
        if(card.getRank() == tempCardToBeMatched.getRank()) {
            tempVec.push_back(card);
            tempCardToBeMatched = card;
        }
    }
    return tempVec;
}

void Player::clearCards() {
    deck.getCards().clear();
    matched.clear();
    unmatched.clear();
}

void Player::discardCard(const Card & card) {
    deck.removeCard(card);
    auto cardFoundInMatched = std::find(matched.begin(), matched.end(), card);
    auto cardFoundInUnmatched = std::find(unmatched.begin(), unmatched.end(), card);

    if(cardFoundInMatched != matched.end())
        matched.erase(cardFoundInMatched);

    if(cardFoundInUnmatched != unmatched.end()) {
        unmatched.erase(cardFoundInUnmatched);
    }
}

int Player::getValueOfUnmatched() const {
    int totalValueOfUnmatched = 0;
    for(const auto& card: unmatched) {
        totalValueOfUnmatched += card.getValue();
    }

    return totalValueOfUnmatched;
}

bool Player::canKnock() const {
    return (getValueOfUnmatched() < 10);
}

bool Player::gin() const {
    return (matched.size() == 10);
}
