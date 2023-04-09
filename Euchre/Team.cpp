#include "Team.h"

Team::Team(Player player1, Player player2, std::string name) 
{
    this->player1 = player1;
    this->player2 = player2;
    this->name = name;
    //Each team needs to have a score relating to rounds won
    //This is what is used to calculate the final winner
    score = 0;
}

std::string Team::getName() { return name; }

int Team::getScore() { return score; }
void Team::increaseScore() { score++; }

std::vector<Player> Team::getPlayers() const
{
    std::vector<Player> players = { player1, player2 };
    return players;
}

int Team::getCombindedPlayersScore(Player player1, Player player2) 
{
    return player1.getScore() + player2.getScore();
}


