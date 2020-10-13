#include <string>
#include <algorithm>
#include "Player.h"

std::string Player::getName() const {
  return name;
}

Card Player::getCard(unsigned int idx) const {
  return hand[idx];
}

void Player::addCard(const Card& c) {
  hand.push_back(c);
}

unsigned int Player::getBooks() const {
  return numBooks;
}

void Player::removeCard(unsigned int idx) {
  hand.erase(hand.begin() + idx);
}

size_t Player::getSize() const {
  return hand.size();
}

void Player::sortHand() {
  std::sort(hand.begin(), hand.end());
}

bool Player::checkForBook(const Card& toCheck) {
  std::sort(hand.begin(), hand.end());

  int num = std::count_if(hand.begin(), hand.end(),
  [&toCheck](Card c){return c.getRank() == toCheck.getRank();});

  if (num == 4) {
    auto it = std::find_if(hand.begin(), hand.end(),
    [&toCheck](Card c){return c.getRank() == toCheck.getRank();});
    hand.erase(it, it + 4);
    numBooks++;
  }

  return num == 4;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
  for (unsigned int i = 0; i < p.hand.size(); i++) {
    os << i << ": " << p.hand[i];
  }

  return os;
}
