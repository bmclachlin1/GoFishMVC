/**
* @author Blake McLachlin
* @date September 29 2020
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#include "Card.h"

/**
* @class Player, representing a player model for a Go Fish game
*/
class Player {
 public:
  /**
  * Constructor for a player object
  * @param n name
  * @return an instantiation of a player object
  */
  Player(const std::string& n) : name(n) { numBooks = 0; }

  /**
  * Destructor for a player object
  */
  virtual ~Player() {}

  /**
  * Getter for player name
  * @return string the player's name
  */
  std::string getName() const;

  /**
  * Get a card from player's hand
  * @param idx the index from which to grab the card from
  * @return Card
  */
  Card getCard(unsigned int idx) const;

  /**
  * Method to add card to player hand. Will need when dealing cards from deck.
  * @param c the card to be added to the player's hand
  */
  void addCard(const Card& c);

  /**
  * Get the number of books the player has
  * @return unsigned int the number of books
  */
  unsigned int getBooks() const;

  /**
  * Remove card at specified index
  * @param idx the index to remove the card from in the Player hand
  */
  void removeCard(unsigned int idx);

  /**
  * Sort the player's hand
  */
  void sortHand();

  /**
  * Determine if player has four-of-a-kind.
  * If so, update numBooks
  * @param toCheck the card to check for 4-of-a-kind of
  * @return bool true if 4-of-a-kind
  */
  bool checkForBook(const Card& toCheck);

  /**
  * Get size of Player hand
  * @return size_t size of Player hand
  */
  size_t getSize() const;

  /**
  * overloaded << operator
  * @param os the output output stream
  * @param p the player to write to the stream 
  * @return output stream representing a Player hand
  */
  friend std::ostream& operator<<(std::ostream& os, const Player& p);

 private:
  unsigned int numBooks; /**< num books a player has */
  std::vector<Card> hand; /**< the player's hand */
  std::string name; /**< the player's name */
};

#endif // PLAYER_H_
