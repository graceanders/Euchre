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

	void Shuffle();
	Card DrawCard();
	void PrintDeck();
private:
	std::vector<Card> deck;
	int currentCardIndex;
};

#endif

