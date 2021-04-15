//
// Created by renew on 4/11/2021.
//

#ifndef GINRUMMYBOT_NODE_H
#define GINRUMMYBOT_NODE_H
#include <vector>
#include <memory>
#include <random>

#include "player.h"

class Node {
public:
    // Might need the deck
    Node(Card cardToInsert, Card discardCard, Deck theDeck, Deck discard, std::vector<Player> player, int turn);
    std::vector<std::shared_ptr<Node>> getChildren() const;
    void addChildren(const std::shared_ptr<Node>& newNode);
//    std::shared_ptr<Node> getNewChild();
    const std::shared_ptr<Node>& getParent() const;
//    Deck getPlayerDeck() const;
    void update(Player player);
    bool canAddChildren() const;
    int getNumSimulations() const;
    Card getDiscardCard() const;

private:
    Card currentInsertCard;
    Card currentDiscardCard;
    Deck mainDeck;
    Deck discardPile;
    std::vector<Player> players;
    int playerTurn;
    std::shared_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children = {};
    int numSimulations;
    std::vector<Card> unusedCards;
    std::uniform_int_distribution<int> dist;
    std::mt19937 mt;
};

#endif //GINRUMMYBOT_NODE_H
