#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card
{
private:
	std::string suit; //
	std::string rank;
	int value;
public:
	Card();
	Card(std::string suit, std::string rank, int value);

	void setSuit(std::string suit);
	std::string getSuit() const;

	void setRank(std::string suit);
	std::string getRank() const;

	void setValue(int value);
	int getValue() const;

};

#endif
