#include <vector>

#include "Player.h"
#include "Card.h"
#include <random>
#include <mutex>

Player::Player() 
{
    name = "Unnamed";
    //Each player needs to have a score realting to trick's won
    score = 0;
}

Player::Player(std::string name) 
{
    this->name = name;
    score = 0;
}

void Player::setName(std::string name) { this->name = name; }
std::string Player::getName() const { return name; }

int Player::getScore() const { return score; }
void Player::increaseScore() { score++; }

void Player::setHand(std::vector<Card>hand) { this->hand = hand; }
void Player::addCardToHand(Card card) { hand.push_back(card); }

void Player::clearHand(std::vector<Card>hand) { hand.clear(); }

//Been having issues with getting a "removeCardFromHand" to work tried a few methods and it always goes back to an issue with '=='
//void Player::removeCardFromHand(Card card)
//{
//    for (size_t i = 0; i < hand.size(); i++) {
//        if (hand[i] == card) {
//            hand.erase(hand.begin() + i);
//            break;
//        }
//    }
//}

std::vector<Card> Player::getHand() const { return hand; }

void Player::printPlayerHand() const
{
    std::vector<Card> hand = this->getHand();
    std::cout << this->getName() << "'s Hand: ";
    for (const auto& card : hand) {
        std::cout << card.getRank() << " of " << card.getSuit() << ", ";
    }
    std::cout << std::endl;
}

Card Player::playCard(std::string suitLed)
{
    // Find the index of the card to play
    int cardIndex = -1;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].getSuit() == suitLed) {
            cardIndex = i;
            break;
        }
    }
    if (cardIndex == -1) {
        // If the player doesn't have a card of the led suit, play a random card
        std::uniform_int_distribution<int> distribution(0, hand.size() - 1);
        std::mt19937 engine(std::chrono::system_clock::now().time_since_epoch().count());
        cardIndex = distribution(engine);
    }

    Card cardPlayed = hand[cardIndex];
    hand.erase(hand.begin() + cardIndex);
    return cardPlayed;
}



