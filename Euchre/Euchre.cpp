#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "Player.h"
#include "Team.h"
#include "Card.h"
#include "Deck.h"
#include "Euchre.h"

using namespace std;

class Trick {
public:
    vector<Card> cards;
    Card trump;
};

void DealCards(int CardsPerPerson, Deck& deck, Player& player1, Player& player2, Player& player3, Player& player4) {
    // Deal CardsPerPerson cards to each player and set the trump card
    for (int i = 0; i < CardsPerPerson; i++) {
        player1.addCardToHand(deck.drawCard());
        player2.addCardToHand(deck.drawCard());
        player3.addCardToHand(deck.drawCard());
        player4.addCardToHand(deck.drawCard());
    }
    //return deck.drawCard();
}

// Define the function to calculate the winner of a trick
int calculateWinner(Trick trick) {
    int highestValue = 0;
    int winnerIndex = 0;

    // Loop through the cards in the trick
    for (int i = 0; i < trick.cards.size(); i++) {
        Card card = trick.cards[i];
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

void playTrick(vector<Player>& players, Trick& trick, const Card& leadingCard)
{
    // Clear the cards from the previous trick
    trick.cards.clear();

    // Add the leading card to the trick
    trick.cards.push_back(leadingCard);

    int currentPlayerIndex = 0;
    int currentHighCardIndex = 0;

    for (int i = 0; i < 3; i++) {
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        Player& currentPlayer = players[currentPlayerIndex];
        Card playedCard = currentPlayer.playCard(leadingCard.getSuit());

        // Add the played card to the trick
        trick.cards.push_back(playedCard);

        // If the played card is of the same suit as the leading card and has a higher rank, update the current high card index
        if (playedCard.getSuit() == leadingCard.getSuit() && playedCard.getRank() > trick.cards[currentHighCardIndex].getRank()) {
            currentHighCardIndex = i + 1;
        }
    }
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
    

    std::cout << "Players in Team 1:\n" 
        << Team1.getPlayers()[0].getName() << " & " << Team1.getPlayers()[1].getName() << "\n"
        << "Players in Team 2:\n" 
        << Team2.getPlayers()[0].getName() << " & " << Team2.getPlayers()[1].getName() << std::endl;

    Deck deck;

    // Shuffle the deck
    deck.shuffle();

    int DealerIndex = 0;
    cout << "Player 1: " << Players[DealerIndex].getName() << " is dealing" << endl;

    Trick trick;
    DealCards(2, deck, Players[0], Players[1], Players[2], Players[3]); //Deals 2 cards

    DealCards(3, deck, Players[0], Players[1], Players[2], Players[3]);

    trick.trump = deck.drawCard();
    cout<<"Trump = "<< trick.trump.getSuit() << std::endl;

    for (const auto& player : Players) {
        player.printPlayerHand();
    }

    int FirstToThow = DealerIndex + 1;
    Card firstPlayed = Players[FirstToThow].getHand()[0];
    cout<< "The first played card is:\n" << firstPlayed.getRank() << " of " << firstPlayed.getSuit() << " (value: " << firstPlayed.getValue() << ")" << 
        "\nPlayed by: " << Players[FirstToThow].getName() << endl;

    playTrick(Players, trick, firstPlayed);

    return 0;
}




