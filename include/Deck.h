/**
* @author Blake McLachlin
* @date September 25 2020
*/

#ifndef DECK_H_
#define DECK_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include "Card.h"

/**
* @class Deck, representing a standard 52-card deck model
*/
class Deck {
 public:
  /**
  * Constructor for a Deck object
  * @return an instantiation of a deck object
  */
  Deck();

  /**
  * Destructor for a Deck object
  */
  virtual ~Deck() {}

  /**
  * Shuffle the deck
  */
  void shuffle();

  /**
  * Remove card at specified index
  * @param idx the index to remove the card from in the deck
  */
  void removeCard(unsigned int idx);

  /**
  * getCard
  * @param idx index in vector to get card from
  * @return Card at index idx
  */
  Card getCard(unsigned int idx) const;

  /**
  * getSize
  * @return size_t size of the deck
  */
  size_t getSize() const;

  /**
  * overloaded equals operator
  * @param rhs the deck to compare to
  * @return true if the decks are the same
  */
  bool operator== (const Deck& rhs) const;

  /**
  * overloaded not equals operator
  * @param rhs the deck to compare to
  * @return true if the decks are not the same
  */
  bool operator!= (const Deck& rhs) const;

  /**
  * overloaded << operator
  * @param os the output stream to write to
  * @param d the deck to write to the output stream
  * @return output stream representing a Deck
  */
  friend std::ostream& operator<<(std::ostream& os, const Deck& d);

 private:
  std::vector<Card> cards; /**< vector of cards */
};

#endif // DECK_H_
