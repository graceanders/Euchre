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
    Team(Player player1, Player player2, std::string name);
    std::string getName();
    int getScore();
    void increaseScore();
    std::vector<Player> getPlayers() const;
};


#endif

