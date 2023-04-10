#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"

class Player 
{
private:
    std::string name;
    int score;
    std::vector<Card> hand;
    bool teamOne;

public:
    Player();
    Player(std::string name);

    void setName(std::string name);
    std::string getName() const;
    
    int getScore() const;
    void increaseScore();

    void resetScore();

    void setHand(std::vector<Card> hand);
    void addCardToHand(Card card);
    void clearHand(std::vector<Card> hand);
    //void removeCardFromHand(Card card);
    std::vector<Card> getHand() const;
    void printPlayerHand() const;
    Card playCard(std::string suitLed);
    void onTeamOne();
    bool getTeamOne();
};

#endif
