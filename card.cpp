//
// Created by renew on 3/18/2021.
//

#include "card.h"
#include <iostream>
Card::Card(const std::string& rank, std::string suit): rank(rank), suit(std::move(suit)), value(giveAValue(rank)) {}

const std::string& Card::getRank() const {
    return rank;
}

const std::string& Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

int giveAValue(const std::string& givenRank) {
    if (!givenRank.empty() && givenRank != "J" && givenRank != "Q" && givenRank != "K" && givenRank != "A") {
        return std::stoi(givenRank);
    } else if (givenRank == "A") {
        return 1;
    } else {
        return 10;
    }
}

bool operator==(const Card& lhs, const Card& rhs) {
    return (lhs.getRank() == rhs.getRank() && lhs.getSuit() == rhs.getSuit());
}
