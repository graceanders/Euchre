#ifndef TEAM_H
#define TEAM_H

#include "Player.h"

class Team {
private:
    Player player1;
    Player player2;
    std::string name;
    int score;
public:
    Team() : player1(), player2(), name(""), score(0) {} 
    Team(Player player1, Player player2, std::string name);
    std::string getName();
    int getScore();
    void increaseScore();
    void decreaseScore();
    std::vector<Player> getPlayers() const;
    int getCombindedPlayersScore(Player player1, Player player2);
};


#endif

