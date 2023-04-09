#include "Trick.h"

bool Trick::CheckForTrump() {
    for (const auto& card : Cards) {
        if (card.getSuit() == trump.getSuit()) {
            TrumpCards.push_back(card);
        }
    }
    return !TrumpCards.empty();
}