//
// Created by renew on 3/18/2021.
//

#include "card.h"
Card::Card(): value(-1) {}

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
    if (!givenRank.empty() && !isAFaceCard(givenRank)) {
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

bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs == rhs);
}

bool isAFaceCard(const std::string& rank) {
    return (rank == "J" || rank == "Q" || rank == "K" || rank == "A");
}

std::ostream& operator<< (std::ostream& output, const Card & card) {
    output << "[" << card.getRank() << ", " << card.getSuit() << ", " << card.getValue() << "] ";
    return output;
}
