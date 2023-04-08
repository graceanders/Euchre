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

using namespace std;

class Trick {
public:
    vector<Card> Cards;
    vector<Card> TrumpCards;
    vector<Player> Players;
    Card trump;
    bool CheckForTrump();
};

bool Trick::CheckForTrump() {
    for (const auto& card : Cards) {
        if (card.getSuit() == trump.getSuit()) {
            TrumpCards.push_back(card);
        }
    }
    return !TrumpCards.empty();
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

bool Bid(vector<Player> Players)
{
    srand(time(NULL));

    for (int i = 0; i < Players.size(); i ++ ) {

        int random_num = rand() % 100 + 1;
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

void Redeal(vector<Player> Players, Deck deck)
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

    Bid(Players);
}

//void playTrick(vector<Player>& players, Trick& trick, const Card& leadingCard)
//{
//    // Clear the cards from the previous trick
//    trick.Cards.clear();
//    trick.Players.clear();
//
//    // Add the leading card to the trick
//    trick.Cards.push_back(leadingCard);
//    trick.Players.push_back(players[0]);
//
//    int currentPlayerIndex = 1;
//    int currentHighCardIndex = 0;
//
//    for (int i = 0; i < 3; i++) {
//        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
//        Player& currentPlayer = players[currentPlayerIndex];
//        Card playedCard = currentPlayer.playCard(leadingCard.getSuit());
//
//        cout << currentPlayer.getName() <<
//            " played " << playedCard.getRank() << " of " << playedCard.getSuit() << endl;
//        // Add the played card to the trick and record the player who played it
//        trick.Cards.push_back(playedCard);
//        trick.Players.push_back(currentPlayer);
//
//        // If the played card is of the same suit as the leading card and has a higher rank, update the current high card index
//        if (playedCard.getSuit() == leadingCard.getSuit() && playedCard.getValue() > trick.Cards[currentHighCardIndex].getValue()) {
//            currentHighCardIndex = i + 1;
//        }
//    }
//    
//
//    if (trick.CheckForTrump()) {
//        cout << "A trump card was played this trick" << endl;
//    }
//    else //If a trump card was not played the point goes to the highest card
//    {
//        cout << "A trump card was not played this trick" << endl;
//        // Award a point to the player who played the highest card
//        trick.Players[currentHighCardIndex].increaseScore();
//
//        cout << "The winning card is " << trick.Cards[currentHighCardIndex].getRank() << " of " << trick.Cards[currentHighCardIndex].getSuit() << endl;
//    }
//}

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
            " played " << playedCard.getRank() << " of " << playedCard.getSuit() << endl;
        // Add the played card to the trick and record the player who played it
        trick.Cards.push_back(playedCard);
        trick.Players.push_back(currentPlayer);
    }

    return trick;

    //// Determine the winner of the trick using the calculateWinner function
    //int winnerIndex = calculateWinner(trick);

    //if (trick.CheckForTrump()) {
    //    cout << "A trump card was played this trick" << endl;
    //}
    //else //If a trump card was not played the point goes to the highest card
    //{
    //    cout << "A trump card was not played this trick" << endl;
    //    // Award a point to the player who played the highest card
    //    trick.Players[winnerIndex].increaseScore();
    //    cout << "The winning card is " << trick.Cards[winnerIndex].getRank() << " of " << trick.Cards[winnerIndex].getSuit() << endl;
    //}
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

int main() 
{

    //Initalize Players
    Player player1("Arron");
    Player player2("Brooklyn");
    Player player3("Caroline");
    Player player4("Damian");

    /*cout << player1.getName() << ": " << player1.getScore() << std::endl;
    cout << player2.getName() << ": " << player2.getScore() << std::endl;

    player1.incrementScore();
    player2.incrementScore();

    std::cout << player1.getName() << ": " << player1.getScore() << std::endl;
    std::cout << player2.getName() << ": " << player2.getScore() << std::endl;*/

    Team Team1(player1, player2, "Team AB");
    Team Team2(player3, player4, "Team CD");

    /*std::cout << team.getName() << ": " << team.getScore() << std::endl;

    team.increaseScore();

    std::cout << team.getName() << ": " << team.getScore() << std::endl;*/

    vector<Player> Players;
    Players.push_back(Team1.getPlayers()[0]);
    Players.push_back(Team2.getPlayers()[1]);
    Players.push_back(Team1.getPlayers()[1]);
    Players.push_back(Team2.getPlayers()[0]);
    
    std::cout << "Team 1: " 
        << Team1.getPlayers()[0].getName() << " & " << Team1.getPlayers()[1].getName() << "\n"
        << "Team 2: " 
        << Team2.getPlayers()[0].getName() << " & " << Team2.getPlayers()[1].getName() << std::endl;

    Deck deck;

    // Shuffle the deck
    deck.Shuffle();

    cout << "\nDealing Phase\n---------------" << endl;
    int DealerIndex = 0;
    cout << Players[DealerIndex].getName() << " is dealing" << endl;

    Trick trick;
    DealCards(2, deck, Players[0], Players[1], Players[2], Players[3]); //Deals 2 cards

    DealCards(3, deck, Players[0], Players[1], Players[2], Players[3]); //Deal 3 cards

    trick.trump = deck.DrawCard();
    cout<<"\nTrump = "<< trick.trump.getSuit() << std::endl;

    cout << "\nBidding Phase\n---------------" << endl;
    if (Bid(Players) == false) { Redeal(Players, deck); }

    int NumTrick = 1;
    cout << "\nTrick #"<< NumTrick << "\n---------------" << endl;
    Card firstPlayed = Players[toTheLeft(DealerIndex, Players)].getHand()[0];
    cout << Players[toTheLeft(DealerIndex, Players)].getName() <<
        " played " << firstPlayed.getRank() << " of " << firstPlayed.getSuit() << endl;

    trick = playTrick(Players, trick, firstPlayed);

    // Determine the winner of the trick using the calculateWinner function
    int winnerIndex = calculateWinner(trick);

    if (trick.CheckForTrump()) {
        cout << "A trump card was played this trick" << endl;
    }
    else //If a trump card was not played the point goes to the highest card
    {
        cout << "A trump card was not played this trick" << endl;
        // Award a point to the player who played the highest card
        trick.Players[winnerIndex].increaseScore();

        cout << "The winning card is " << trick.Cards[winnerIndex].getRank() << " of " << trick.Cards[winnerIndex].getSuit() << endl;
    }


    return 0;
}
