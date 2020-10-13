/**
* @author Blake McLachlin
* @date October 7 2020
*/

#ifndef GO_FISH_CONTROLLER_H_
#define GO_FISH_CONTROLLER_H_

#include <string>
#include <vector>
#include "GoFishView.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

/**
* @class GoFishController The controller for our Go Fish game
*/
class GoFishController {
 public:
  /**
  * Constructor for a GoFishController object
  * @param deck the go fish Deck model
  * @param ui the GoFishView
  */
  GoFishController(Deck* deck, GoFishView* ui);

  /**
  * Destructor
  */
  virtual ~GoFishController();

  /**
  * Initializes the game
  */
  void init();

  /**
  * Calls ui/view to display the user's hand
  * @param which picks which of the player's to display
  */
  void displayHand(int which);

  /**
  * Deals the cards to the players
  */
  void dealCards();

  /**
  * Function to start playing of the Game
  * @precondition: must be called after init
  */
  void playGame();

  /**
  * Function for user to play their turn
  */
  void playTurn();

  /**
  * Function for computer to play its turn
  * @param idx the index in the players vector of who's turn it is
  */
  void computerTurn(unsigned int idx);

  /**
  * See if a player's hand contains Card
  * @param c the card to check for
  * @param idx the player you are asking for card from
  * @return bool true if there's a match
  */
  bool findMatch(const Card& c, unsigned int idx);

  /**
  * Determine if game is over
  * @return bool true if game is over
  */
  bool endGame();

  /**
  * Display the winner of the game
  */
  void displayWinner();

  /**
  * Getter for number of players in game. Needed since Constructor
  * doesn't include players and this is left to the menu.
  * @return size_t the number of players
  */
  size_t numPlayers() const;

 private:
  std::vector<Player*> players; /**< player model for our application */
  Deck* deck; /**< deck model for our application */
  GoFishView* ui; /**< view for our application */
};

#endif // GO_FISH_CONTROLLER_H_
