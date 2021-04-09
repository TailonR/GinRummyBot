//
// Created by renew on 3/31/2021.
//

#ifndef GINRUMMYBOT_CARDPROPERTIES_H
#define GINRUMMYBOT_CARDPROPERTIES_H
#include <vector>
#include <string>
struct CardProperties {
    static const std::vector<std::string>& getCardRanks() {
        static std::vector<std::string> cardRanks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        return cardRanks;
    }
    static const std::vector<std::string>& getCardSuits() {
        static std::vector<std::string> cardSuits = {"club", "diamond", "heart", "spade"};
        return cardSuits;
    }
};
#endif //GINRUMMYBOT_CARDPROPERTIES_H
