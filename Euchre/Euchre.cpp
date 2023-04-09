#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

#include "Player.h"
#include "Team.h"
#include "Card.h"
#include "Deck.h"
#include "Euchre.h"
#include "Trick.h"

using namespace std;
 
vector<Player> Players;
Team Team1;
Team Team2;

vector<Player> IniatalizePlayers() 
{
    Player player1("Arron"); 
    Player player2("Brooklyn"); 
    Player player3("Caroline"); 
    Player player4("Damian"); 

    Team1 = Team(player1, player2, "Team AB"); 
    Team2 = Team(player3, player4, "Team CD"); 
    
    Players.push_back(Team1.getPlayers()[0]); 
    Players.push_back(Team2.getPlayers()[1]); 
    Players.push_back(Team1.getPlayers()[1]); 
    Players.push_back(Team2.getPlayers()[0]);

    std::cout << "Team 1: "
        << Team1.getPlayers()[0].getName() << " & " << Team1.getPlayers()[1].getName() << "\n"
        << "Team 2: "
        << Team2.getPlayers()[0].getName() << " & " << Team2.getPlayers()[1].getName() << std::endl;

    return Players; 
}

void DealCards(int CardsPerPerson, Deck& deck, Player& player1, Player& player2, Player& player3, Player& player4) {
    // Deal CardsPerPerson cards to each player and set the trump card
    for (int i = 0; i < CardsPerPerson; i++) {
        player1.addCardToHand(deck.DrawCard());
        player2.addCardToHand(deck.DrawCard());
        player3.addCardToHand(deck.DrawCard());
        player4.addCardToHand(deck.DrawCard());
    }
}

bool Bid(vector<Player> Players)// Refrenced: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range/7560564#7560564
{
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(1, 100); 

    for (int i = 0; i < Players.size(); i++) {

        int random_num = dis(gen);
        if (random_num > 50) {
            cout << Players[i].getName() << " called trump" << endl; 
            return true;
        }
        else
            cout << Players[i].getName() << " passed" << endl; 
    }

    cout << "No players called trump" << endl;
    return false;
}

void Redeal(vector<Player> Players, Deck deck, Trick trick)
{
    //Clear all of the players hands
    for (int i = 0; i < Players.size(); i++) 
    {
        Players[i].clearHand(Players[i].getHand());
    }

    //Shuffle deck
    deck.Shuffle();

    DealCards(2, deck, Players[0], Players[1], Players[2], Players[3]); //Deals 2 cards

    DealCards(3, deck, Players[0], Players[1], Players[2], Players[3]); //Deal 3 cards

    trick.trump = deck.DrawCard();
    cout << "\nTrump = " << trick.trump.getSuit() << std::endl;

    Bid(Players);
}

Trick playTrick(vector<Player>& players, Trick& trick, const Card& leadingCard)
{
    // Clear the cards from the previous trick
    trick.Cards.clear();
    trick.Players.clear();

    // Add the leading card to the trick
    trick.Cards.push_back(leadingCard);
    trick.Players.push_back(players[0]);

    int currentPlayerIndex = 1;

    for (int i = 0; i < 3; i++) {
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        Player& currentPlayer = players[currentPlayerIndex];
        Card playedCard = currentPlayer.playCard(leadingCard.getSuit());

        cout << currentPlayer.getName() <<
            ": " << playedCard.getRank() << " of " << playedCard.getSuit() << " | ";
        // Add the played card to the trick and record the player who played it
        trick.Cards.push_back(playedCard);
        trick.Players.push_back(currentPlayer);
    }
    cout << endl;

    return trick;
}


// Define the function to calculate the winner of a trick
int calculateWinner(Trick trick) {
    int highestValue = 0;
    int winnerIndex = 0;

    // Loop through the cards in the trick
    for (int i = 0; i < trick.Cards.size(); i++) {
        Card card = trick.Cards[i];
        int value = card.getValue();

        // If the card is of the trump suit, multiply its value by 10
        if (card.getSuit() == trick.trump.getSuit()) {
            value *= 10;
        }

        // If the card has a higher value than the current highest value, update the highest value and winner index
        if (value > highestValue) {
            highestValue = value;
            winnerIndex = i;
        }
    }

    return winnerIndex;
}

int toTheLeft(int current, vector<Player> Players)
{
    int next = current;
    next++;
    if (next < Players.size()) {
        current++;
    }
    else
        current = 0;

    return current;
}



//Phases

void DealPhase(vector<Player>& Players, Deck& deck, int& DealerIndex, Trick trick)
{
    cout << "\n" << Players[DealerIndex].getName() << " is dealing" << endl;

    DealCards(2, deck, Players[0], Players[1], Players[2], Players[3]); //Deals 2 cards 

    DealCards(3, deck, Players[0], Players[1], Players[2], Players[3]); //Deal 3 cards 

    trick.trump = deck.DrawCard();
    cout << "\nTrump = " << trick.trump.getSuit() << std::endl;
}

void TrickPhase(vector<Player>& Players, Deck& deck, int& DealerIndex, Trick trick)
{
    for (int i = 1; i <= 5; i++) //Run through 5 tricks
    {
        cout << "\nTrick #" << i << "\n---------------" << endl;
        Card firstPlayed = Players[toTheLeft(DealerIndex, Players)].getHand()[0];
        cout << Players[toTheLeft(DealerIndex, Players)].getName() <<
            ": " << firstPlayed.getRank() << " of " << firstPlayed.getSuit() << " | ";

        trick = playTrick(Players, trick, firstPlayed);

        // Determine the winner of the trick using the calculateWinner function
        int winnerIndex = calculateWinner(trick);
        Player winningPlayer = trick.Players[winnerIndex];

        if (trick.CheckForTrump()) { cout << "A trump card was played this trick" << endl; }
        else{ cout << "A trump card was not played this trick" << endl; }

        cout << "The winning card is " << trick.Cards[winnerIndex].getRank() << " of " << trick.Cards[winnerIndex].getSuit() << " played by " << winningPlayer.getName() << endl;
        Players[winnerIndex].increaseScore();

        DealerIndex = toTheLeft(DealerIndex, Players);
    }
}

void PointPhase(vector<Player>& Players)
{
    cout << "\nPoints " << "\n---------------" << endl;
    for (int i = 0; i < Players.size(); i++)
    {
        cout << Players[i].getName() << ": " << Players[i].getScore() << endl;
    }
}

int main() 
{
    Players = IniatalizePlayers();

    while (Team1.getScore() < 10 && Team2.getScore() < 10) 
    {
        for (int i = 0; i < Players.size(); i++)
        { 
            Players[i].resetScore(); 
        }

        Deck deck;
        deck.Shuffle();

        int DealerIndex = 0;
        Trick trick;

        //Deal
        DealPhase(Players, deck, DealerIndex, trick);

        //Bid
        cout << "\nBidding Phase\n---------------" << endl;
        bool hasBid;
        do {
            hasBid = Bid(Players);
            if (!hasBid) { Redeal(Players, deck, trick); }
        } while (!hasBid);


        //Trick
        TrickPhase(Players, deck, DealerIndex, trick);

        //Points
        PointPhase(Players);

        int Team1Points = Team1.getCombindedPlayersScore(Players[0], Players[2]);
        int Team2Points = Team2.getCombindedPlayersScore(Players[1], Players[3]);

        if (Team1Points > Team2Points)
        {
            cout << "\nTeam 1 won " << Team1Points << " tricks, and won that round" << endl;
            Team1.increaseScore();
        }
        else
        {
            cout << "\nTeam 2 won " << Team2Points << " tricks, and won that round" << endl;
            Team2.increaseScore();
        }

        cout << "Team 1 Score: " << Team1.getScore() << " | Team 2 Score: " << Team2.getScore() << endl;
    }
    
    if (Team1.getScore() == 10) { cout << "\nTeam 1 won!" << endl; }
    else{ cout << "\nTeam 2 won!" << endl; }

    return 0;
}