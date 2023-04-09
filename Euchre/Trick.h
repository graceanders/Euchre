#ifndef TRICK_H
#define TRICK_H

#include <vector>
#include "Card.h"
#include "Player.h"

class Trick {
public:
    std::vector<Card> Cards;
    std::vector<Card> TrumpCards;
    std::vector<Player> Players;
    Card trump;
    bool CheckForTrump();
};

#endif
