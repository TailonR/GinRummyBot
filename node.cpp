//
// Created by renew on 4/11/2021.
//

#include "node.h"

#include <utility>

Node::Node(Card cardToInsert, Card discardCard, Deck theDeck, Deck discard, std::vector<Player> thePlayers, int turn):
        currentInsertCard(cardToInsert),
       currentDiscardCard(discardCard),
       mainDeck(std::move(theDeck)),
       discardPile(std::move(discard)),
       players(std::move(thePlayers)),
       playerTurn(turn),
       parent(nullptr),
       numSimulations(0),
       mt(std::random_device{}()),
//       unusedCards(thePlayers[turn].getCards()),
       dist(0, 11)
       {}

std::vector<std::shared_ptr<Node>> Node::getChildren() const {
    return children;
}


void Node::addChildren(const std::shared_ptr<Node> &node) {
    //// NEED TO ADD LOGIC TO THIS
//    auto newBoard = Node->board;
//    auto newMove = Node->unvisitedSpaces[Node->dist(Node->mt)];
//    Node->unvisitedSpaces.erase(std::find(Node->unvisitedSpaces.begin(), Node->unvisitedSpaces.end(), newMove));
//
//    if(Node->playerTurn)
//        Node->players[1].makeMove(newBoard, std::get<0>(newMove), std::get<1>(newMove));
//    else
//        Node->players[0].makeMove(newBoard, std::get<0>(newMove), std::get<1>(newMove));
//
//    auto newNode = std::make_shared<Node>(newBoard, newMove, Node->players, !(Node->playerTurn));
//    newNode->parent = Node;
//    Node->children.emplace_back(newNode);

//    initializeRandomNumberGenerator(10);
//    discardIndex = generateRandomNumber();
//    if (discardIndex < 10) {
//        auto discardCard = players[turn].getCards()[discardIndex];
//        players[turn].makeMove(topCard, discardCard, discard);
//    }

    // Copy next player's hand
    auto newHand = node->players[playerTurn].getCards();

    // Copy main deck
    auto newMainDeck = node->mainDeck;

    // Copy discard pile
    auto newDiscardPile = node->discardPile;

    // Find the the card to discard
    int discardIndex = node->dist(node->mt);
    auto discardCard = newHand[discardIndex];

    // The card to insert
    auto insertCard = newMainDeck.topCard();

    if(discardIndex != 0) { // if the discardIndex isn't where the new card will be
        // next player's move
//        node->players[playerTurn].makeMove(insertCard, discardCard, newDiscardPile);

        // Remove the top card from the main deck
//        newMainDeck.removeCard(newMainDeck.topCard());
    } else {
        // add the card to the discard pile
        newDiscardPile.addCard(newMainDeck.topCard());

        // Remove the top card from the main deck
//        newMainDeck.removeCard(newMainDeck.topCard());
    }

    node->unusedCards.erase(std::find(node->unusedCards.begin(), node->unusedCards.end(), discardCard));
//    auto newNode = std::make_shared<Node>(insertCard, discardCard, newMainDeck, newDiscardPile, players, (node->playerTurn? 0: 1));
}

const std::shared_ptr<Node> & Node::getParent() const {
    return parent;
}

void Node::update(Player player) {
    //// NEED TO ADD LOGIC TO THIS
}

bool Node::canAddChildren() const {
    return !unusedCards.empty();
}

int Node::getNumSimulations() const {
    return numSimulations;
}

Card Node::getDiscardCard() const {
    return currentDiscardCard;
}
