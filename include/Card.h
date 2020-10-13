/**
* @author Blake McLachlin
* @date September 21 2020
*/

#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>

/**
* @class Card, representing a card model from a standard 52-card deck
*/
class Card {
 public:
  /**
  * @brief enumeration for card ranks
  */
  enum Rank {
    Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
  };

  /**
  * @brief enumeration for card suits
  */
  enum Suit {
    Spades, Clubs, Hearts, Diamonds
  };

  /**
  * Constructor for a Card object
  * @param r rank
  * @param s suit
  * @return an instantiation of a card object
  */
  Card(Rank r = Ace, Suit s = Spades) : cardRank(r), cardSuit(s) {}

  /**
  * Destructor for a Card object
  */
  virtual ~Card() {}

  /**
  * Getter for Card Rank
  * @return the Cards Rank
  */
  Rank getRank() const;

  /**
  * Setter for Card Rank
  * @param r the new Rank
  */
  void setRank(const Rank& r);

  /**
  * Getter for Card Suit
  * @return the Cards Suit
  */
  Suit getSuit() const;

  /**
  * Setter for Card Suit
  * @param s the new Suit
  */
  void setSuit(const Suit& s);

  /**
  * converts enum Rank to string equivalent
  * @param r the cards rank
  * @return std::string the string value of rank
  */
  std::string rankToString(const Rank& r);

  /**
  * converts enum Suit to string equivalent
  * @param s the cards suit
  * @return std::string the string value of suit
  */
  std::string suitToString(const Suit& s);

  /**
  * overloaded equals operator
  * @param rhs the card to compare to
  * @return true if the cards are the same
  */
  bool operator== (const Card& rhs) const;

  /**
  * overloaded not equals operator
  * @param rhs the card to compare to
  * @return true if the cards are not the same
  */
  bool operator!= (const Card& rhs) const;

  /**
  * used for sorting
  * @param rhs the card to compare to
  * @return true if (*this) < rhs
  */
  bool operator< (const Card& rhs) const;

  /**
  * overloaded << operator
  * @param os the output stream
  * @param c the card we write to the output stream
  * @return output stream representing a Card
  */
  friend std::ostream& operator<<(std::ostream& os, const Card& c);

 private:
  Rank cardRank; /**< Card's Rank */
  Suit cardSuit; /**< Card's Suit */
};

#endif // CARD_H_
