#include "Card.h"
#include <iostream>
#include <string>
#include <utility>

Card::Rank Card::getRank() const {
  return cardRank;
}

void Card::setRank(const Rank& r) {
  cardRank = r;
}

Card::Suit Card::getSuit() const {
  return cardSuit;
}

void Card::setSuit(const Suit& s) {
  cardSuit = s;
}

std::string Card::rankToString(const Rank& r) {
  switch (r) {
    case Ace: return "Ace";
    case Two: return "2";
    case Three: return "3";
    case Four: return "4";
    case Five: return "5";
    case Six: return "6";
    case Seven: return "7";
    case Eight: return "8";
    case Nine: return "9";
    case Ten: return "10";
    case Jack: return "Jack";
    case Queen: return "Queen";
    case King: return "King";
    default: return "Invalid Rank";
  }
}

std::string Card::suitToString(const Suit& s) {
  switch (s) {
    case Spades: return "Spades";
    case Clubs: return "Clubs";
    case Hearts: return "Hearts";
    case Diamonds: return "Diamonds";
    default: return "Invalid Suit";
  }
}

bool Card::operator== (const Card& rhs) const {
  return cardRank == rhs.cardRank && cardSuit == rhs.cardSuit;
}

bool Card::operator!=(const Card& rhs) const {
  return !((*this) == rhs);
}

bool Card::operator< (const Card& rhs) const {
  return std::make_pair(cardRank, cardSuit) <
         std::make_pair(rhs.getRank(), rhs.getSuit());
}

std::ostream& operator<< (std::ostream& os, const Card& c) {
  Card card = c;
  os << card.rankToString(c.cardRank) << ":" <<
  card.suitToString(c.cardSuit) << std::endl;
  return os;
}
