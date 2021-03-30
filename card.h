//
// Created by renew on 3/18/2021.
//

#ifndef GINRUMMYBOT_CARD_H
#define GINRUMMYBOT_CARD_H
#include <string>
#include <vector>
class Card {
public:
    Card(const std::string&, std::string);
    const std::string& getRank() const;
    const std::string& getSuit() const;
    int getValue() const;
private:
    std::string rank;
    std::string suit;
    int value;
};

int giveAValue(const std::string&);
bool operator==(const Card&, const Card&);
#endif //GINRUMMYBOT_CARD_H
