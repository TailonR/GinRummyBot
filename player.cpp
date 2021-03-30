//
// Created by renew on 3/18/2021.
//

#include "player.h"
Player::Player(): deck(Deck(true)) {}

Deck Player::getDeck() const {
    return deck;
}

int Player::getNumOfCards() {
    return deck.getNumCards();
}

void Player::addCard(const Card& newCard) {
    for(auto& card: deck.getCards()) {
        if(card.getRank().empty() && card.getSuit().empty()) {
            card = newCard;
            break;
        }
    }
}
