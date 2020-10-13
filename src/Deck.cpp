#include "Deck.h"

constexpr unsigned int DECK_SIZE = 52;
constexpr unsigned int NUM_RANKS = 13;
constexpr unsigned int NUM_SUITS = 4;

Deck::Deck() {
  for (unsigned int j = 0; j < NUM_SUITS; j++)
    for (unsigned int i = 0; i < NUM_RANKS; i++)
      cards.push_back
      (Card(static_cast<Card::Rank>(i), static_cast<Card::Suit>(j)));
}

void Deck::shuffle() {
  auto seed = std::default_random_engine {};
  std::shuffle(cards.begin(), cards.end(), seed);
}

void Deck::removeCard(unsigned int idx) {
  cards.erase(cards.begin() + idx);
}

Card Deck::getCard(unsigned int idx) const {
  return cards[idx];
}

size_t Deck::getSize() const {
  return cards.size();
}

bool Deck::operator==(const Deck& rhs) const {
  if (cards.size() != rhs.getSize())
    return false;

  for (unsigned int i = 0; i < cards.size(); i++)
    if (cards[i] != rhs.getCard(i))
      return false;

  return true;
}

bool Deck::operator!= (const Deck& rhs) const {
  return !((*this) == rhs);
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
  for (unsigned int i = 0; i < DECK_SIZE; i++) {
    os << d.cards[i];
  }

  return os;
}
