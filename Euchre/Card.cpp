#include "Card.h"
#include <iostream>

using namespace std;

Card::Card() 
{
	suit = "Undecided";
	rank = "Undecided";
	value = 0;
}

Card::Card(std::string suit, std::string rank, int value) 
{
	this->suit = suit;
	this->rank = rank;
	this->value = value;
}

void Card::setSuit(string suit) { this->suit = suit; }
string Card::getSuit() const { return suit; }

void Card::setRank(string rank) { this->rank = rank; }
string Card::getRank() const { return rank; }

void Card::setValue(int value) { this->value = value; }
int Card::getValue() const { return value; }


