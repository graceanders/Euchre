#include "Card.h"
#include "Deck.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

Deck::Deck() : currentCardIndex(0) {
    // Initialize the deck with all possible cards

    // Initialize the suits and ranks
    std::vector<std::string> suits = { "Clubs", "Diamonds", "Hearts", "Spades" };
    std::vector<std::string> ranks = { "Jack", "Ace", "King", "Queen", "Ten", "Nine" };
    std::vector<int> values = { 14, 13, 12, 11, 10, 9 };

    // Initialize the deck
    for (int i = 0; i < suits.size(); i++) {
        for (int j = 0; j < ranks.size(); j++) {
            Card card;
            card.setSuit(suits[i]);
            card.setRank(ranks[j]);
            card.setValue(values[j]);
            deck.push_back(card);
        }
    }
}

void Deck::shuffle() {
    // Shuffle the deck using the Fisher-Yates algorithm
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    currentCardIndex = 0;
}

Card Deck::drawCard() {
    // Return the next card in the deck and increment the counter
    Card card = deck[currentCardIndex];
    ++currentCardIndex;
    return card;
}

void Deck::printDeck()
{
    for (int i = 0; i < deck.size(); i++) {
        std::cout << deck[i].getRank() << " of " << deck[i].getSuit() << " (value: " << deck[i].getValue() << ")" << std::endl;
    }
}
