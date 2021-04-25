//
// Created by renew on 3/31/2021.
//

#ifndef GINRUMMYBOT_CARDPROPERTIES_H
#define GINRUMMYBOT_CARDPROPERTIES_H
#include <vector>
#include <string>
#include <iostream>
struct CardProperties {
    // Suits are represented as numbers from 0 to 3
    //      0 - Hearts
    //      1 - Diamonds
    //      2 - Spades
    //      3 - Clubs
    // Ranks are represented as numbers from 0 to 12
    //      1 - A
    //      10 - J
    //      11 - Q
    //      12 - K
    //      everything else: the rank is the number (e.g 2 - 2, 3 - 3)
    CardProperties() {
        for(int suit = 0; suit < 4; suit++) {
            std::vector<int> row;
            for(int rank = 0; rank <= 13; rank++) {
                if(rank == 0) {
                    row.push_back(0);
                } else if (rank >= 10) {
                    row.push_back(10);
                } else {
                    row.push_back(rank);
                }
            }
            cards.push_back(row);
        }
    }

    enum CardStates {STOCK = 0, TOPSTOCK = 1, DISCARD = 2, TOPDISCARD = 3, P0CARD = 4, P1CARD = 5};


    std::vector<std::vector<int>> cards;
};
#endif //GINRUMMYBOT_CARDPROPERTIES_H
