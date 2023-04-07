#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

class Deck {
public:
	Deck();

	void shuffle();
	Card drawCard();
	void printDeck();
private:
	std::vector<Card> deck;
	int currentCardIndex;
};

#endif

