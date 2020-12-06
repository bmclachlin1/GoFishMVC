/**
* @author Blake McLachlin
* @date October 7 2020
*/

#ifndef GO_FISH_VIEW_H_
#define GO_FISH_VIEW_H_

#include <iostream>
#include <vector>
#include <string>
#include "Deck.h"
#include "Card.h"
#include "Player.h"

/**
* @class GoFishView the view for our go fish game
*/
class GoFishView {
 public:
  /**
  * display player's hand to console
  * @param p the player we are displaying
  */
  void showHand(Player* p);

  /**
  * display game menu to player and get input from user
  * @return the user's choice
  */
  int showMenu();

  /**
  * Used to ask how many players are wanted in game
  * @return the number of players
  */
  int howMany();

  /**
  * Asks user for their name and assigns names to CPU's
  * @param howMany the number of players
  * @return the player names
  */
  std::vector<std::string> playerNames(int howMany);

  /**
  * Display player's and get player to pick which player to ask
  * for cards from
  * @param numPlayers the number of players
  * @return the player's pick
  */
  unsigned int pickPlayerToAsk(unsigned int numPlayers);

  /**
  * Asks the user to pick a card from their hand to fish for
  * @param p the player picking the card
  */
  Card pickCard(Player* p);

  /**
  * Show player which card they get
  * @param c the card to display
  */
  void playerGetsCard(const Card& card);

  /**
  * Display which card cpu gets
  * @param c the card they get
  * @param idx the index of cpu player in players vector
  */
  void cpuGetsCard(const Card& card, unsigned int idx);

  /**
  * Show's help menu for game
  */
  void help();

  /**
  * Show a small message to console
  * @param msg the message to show
  */
  void simpleMessage(const std::string& msg);

  /**
  * displays an error message to the console
  * @param err the error message to be displayed
  */
  void error(const std::string& err);
};

#endif // GO_FISH_VIEW_H_
